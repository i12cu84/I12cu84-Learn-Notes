# <a name="main"></a>C++ 核心指导方针

### <a name="Rf-consume"></a>F.18: 对于“将被移动（will-move-from）”参数，按 `X&&` 进行传递并对参数 `std::move`

##### 理由

这样做很高效，并且消除了调用点的 BUG：`X&&` 绑定到右值，而要传递左值的话则要求在调用点明确进行 `std::move`。

##### 示例

    void sink(vector<int>&& v)  // 无论参数所拥有的是什么，sink 都获得了其所有权
    {
        // 通常这里可能有对 v 的 const 访问
        store_somewhere(std::move(v));
        // 通常这里不再会使用 v 了；它已经被移走
    }

注意，`std::move(v)` 使得 `store_somewhere()` 可以把 `v` 遗留为被移走的状态。
[这可能很危险](#Rc-move-semantic)。


##### 例外

只能移动并且移动廉价的唯一拥有者类型，比如 `unique_ptr`，也可以按值传递，这样写起来更简单而且效果相同。按值传递确实产生了一次额外的（廉价）移动操作，但我们更加优先于简单性和清晰性。

例如：

    template<class T>
    void sink(std::unique_ptr<T> p)
    {
        // 使用 p ... 可能在之后的什么地方 std::move(p)
    }   // p 被销毁

##### 强制实施

* 对于所有 `X&&` 参数（其中的 `X` 不是模板类型参数的名字），如果函数体中使用它时没有用 `std::move`，就将其标明。
* 标明对已经被移动过的对象的访问。
* 不要有条件地从对象进行移动。

### <a name="Rf-ptr-ref"></a>F.60: 当“没有参数”是有效的选项时，采用 `T*` 优先于 `T&`

### <a name="Rf-return-ref"></a>F.44: 当不想进行复制，而“没有对象被返回”不是有效的选项时，返回 `T&`

### <a name="Rf-assignment-op"></a>F.47: 赋值运算符返回 `T&`

##### 理由

运算符重载的惯例（尤其是对于具体类型来说），是让
`operator=(const T&)` 实施赋值之后返回（非 `const`）的
`*this`。这就确保了与标准库类型之间的一致性，并遵从了
“像 `int` 一样工作”的原则。

##### 注解

历史上层有过一些建议让赋值运算符返回 `const T&`。
这主要是为了避免 `(a = b) = c` 形式的代码 —— 这种代码其实并不常见到足以成为违反与标准类型之间一致性的理由。

##### 示例

    class Foo
    {
     public:
        ...
        Foo& operator=(const Foo& rhs)
        {
          // 复制各个成员。
          ...
          return *this;
        }
    };

##### 强制实施

应当通过工具对所有赋值运算符的返回类型（和返回值）进行检查
来强制实施。

### <a name="Rc-five"></a>C.21: 如果定义或者 `=delete` 了任何复制、移动或析构函数，请定义或者 `=delete` 它们全部


##### 注解

编译器会很大程度上强制实施这条规则，并在理想情况下会对任何违反都给出警告。

在带有析构函数的类中，依靠隐式生成的复制操作的做法已经被摒弃。

编写这些函数很容易出错。
注意它们的参数类型：

    class X {
    public:
        // ...
        virtual ~X() = default;            // 析构函数 (如果 X 是基类，用 virtual)
        X(const X&) = default;             // 复制构造函数
        X& operator=(const X&) = default;  // 复制赋值
        X(X&&) = default;                  // 移动构造函数
        X& operator=(X&&) = default;       // 移动赋值
    };

一个小错误（例如拼写错误，遗漏 `const`，使用 `&` 而不是 '&&`，或遗漏一个特殊功能）可能导致错误或警告。
为避免单调乏味和出错的可能性，请尝试遵循[零规则](＃Rc-zero)。

##### 强制实施

【简单】 类中应当要么为每个复制/移动/析构函数都提供一个声明（即便是 `=delete`），要么都不这样做。

### <a name="Rc-default0"></a>C.43: 保证可复制类带有默认构造函数
##### 强制实施

* 对于可用 `=` 进行复制的类，若没有默认构造函数则对其进行标记。
* 对于可用 `==` 进行比较但不可复制的类进行标记。
### <a name="Rc-explicit"></a>C.46: 默认情况下，把单参数的构造函数声明为 `explicit`

##### 理由

用以避免意外的类型转换。

##### 示例，不好

    class String {
    public:
        String(int);   // 不好
        // ...
    };

    String s = 10;   // 意外: 大小为 10 的字符串

##### 例外

如果确实想要从构造函数参数类型隐式转换为类类型的话，就不使用 `explicit`：

    class Complex {
    public:
        Complex(double d);   // OK: 希望进行从 d 向 {d, 0} 的转换
        // ...
    };

    Complex z = 10.7;   // 无意外的转换

**参见**: [有关隐式转换的讨论](#Ro-conversion)

##### 注解

不应当将复制和移动构造函数作为 `explicit` 的，因为它们并不进行转换。显式的复制/移动构造函数会把按值传递和返回变麻烦。

##### 强制实施

【简单】 单参数的构造函数应当声明为 `explicit`。有益的单参数非 `explicit` 构造函数在大多数代码库中都是很少见的。对没在“已确认列表”中列出的每个违规都要给出警告。

### <a name="Rc-factory"></a>C.50: 当初始化过程中需要体现“虚函数行为”时，请使用工厂函数

##### 理由

当基类对象的状态必须依赖于对象的派生部分的状态时，需要使用虚函数（或等价手段），并最小化造成误用和不完全构造的对象的机会窗口。

##### 注解

工厂的返回类型默认情况下通常应当为 `unique_ptr`；如果某些用法需要共享，则调用方可以将这个 `unique_ptr` `move` 到一个 `shared_ptr` 中。但是，如果工厂的作者已知其所返回的对象的所有用法都是共享使用的话，就可返回 `shared_ptr`，并在函数体中使用 `make_shared` 以节省一次分配。

##### 示例，不好

    class B {
    public:
        B()
        {
            /* ... */
            f(); // 不好: C.82：不要在构造函数和析构函数中调用虚函数
            /* ... */
        }

        virtual void f() = 0;
    };

##### 示例

    class B {
    protected:
        class Token {};

    public:
        explicit B(Token) { /* ... */ }  // 创建不完全初始化的对象
        virtual void f() = 0;

        template<class T>
        static shared_ptr<T> create()    // 创建共享对象的接口
        {
            auto p = make_shared<T>(typename T::Token{});
            p->post_initialize();
            return p;
        }

    protected:
        virtual void post_initialize()   // 构造之后立即调用
            { /* ... */ f(); /* ... */ } // 好: 虚函数分派是安全的
    };

    class D : public B {                 // 某个派生类
    protected:
        class Token {};

    public:
        explicit D(Token) : B( B::Token{} ) {}
        void f() override { /* ... */ };

    protected:
        template<class T>
        friend shared_ptr<T> B::create();
    };

    shared_ptr<D> p = D::create<D>();  // 创建一个 D 的对象

`make_shared` 要求公开的构造函数。构造函数通过要求一个受保护的 `Token` 而无法再被公开调用，从而避免不完全构造的对象泄漏出去。
通过提供工厂函数 `create()`，（在自由存储上）构造对象变得简便。

##### 注解

根据惯例，工厂方法在自由存储上进行分配，而不是在运行栈或者某个外围对象之内进行。

### <a name="Rc-copy-assignment"></a>C.60: 使复制赋值非 `virtual`，接受 `const&` 的参数，并返回非 `const` 的引用

### <a name="Rc-copy-self"></a>C.62: 使复制赋值可以安全进行自赋值

##### 理由

如果 `x=x` 会改变 `x` 的值的话，会让人惊异，并导致发生严重的错误（通常会含有资源泄漏）。

    Foo& Foo::operator=(const Foo& a)   // 更简单，而且可能也更好
    {
        s = a.s;
        i = a.i;
        return *this;
    }

`std::string` 的自赋值是安全的，`int` 也是如此。所有的成本都将花在（罕见的）自赋值情况中。

##### 强制实施

【简单】 赋值运算符不应当包含 `if (this == &a) return *this;` 这样的代码模式 ???

### <a name="Rc-move-assignment"></a>C.63: 使移动赋值非 `virtual`，接受 `&&` 的参数，并返回非 `const&`

##### 理由

这样简单而且高效。

**参见**: [针对复制赋值的规则](#Rc-copy-assignment)。

##### 强制实施

和针对[复制赋值](#Rc-copy-assignment)所做的相同。

* 【简单】 赋值运算符不能为 `virtual`。有怪兽出没！
* 【简单】 赋值运算符应当返回 `T&` 以支持调用链，不要改为如 `const T&` 等类型，这样会影响可组合性以及把对象放入容器的能力。
* 【中等】 移动赋值运算符应当（隐式或者显式）调用所有的基类和成员的移动赋值运算符。

### <a name="Rc-move-semantic"></a>C.64: 移动操作应当进行移动，并使原对象处于有效状态

### <a name="Rc-move-self"></a>C.65: 使移动赋值可以安全进行自赋值

##### 理由

如果 `x = x` 会改变 `x` 的值的话，会让人惊异，并导致发生严重的错误（通常会含有资源泄漏）。不过，通常不会有人写出能够变成移动操作的自赋值代码，但它确实是会发生的。不管怎样，`std::swap` 就是利用移动操作来实现的，因此如果你不小心写了 `swap(a, b)` 而 `a` 和 `b` 指代相同的对象的话，未能处理自移动情况将是一种严重而且微妙的错误。

##### 示例

    class Foo {
        string s;
        int i;
    public:
        Foo& operator=(Foo&& a);
        // ...
    };

    Foo& Foo::operator=(Foo&& a) noexcept  // OK，但增加了成本
    {
        if (this == &a) return *this;  // 这行是多余的
        s = std::move(a.s);
        i = a.i;
        return *this;
    }

[自赋值](#Rc-copy-self)中反对 `if (this == &a) return *this;` 测试的“每一百万次有一次”的论点，在自移动的情况中更加适当。

##### 强制实施

* 【中级】 在自赋值的情况中，移动赋值运算符不应当使持有已经被 `delete` 或设为 `nullptr` 的指针成员。
* 【无法强制实施】 查看标准库容器类型（包括 `string`）的使用方式，在普通（非性命攸关）使用中将它们当作是安全的。

### <a name="Rc-copy-virtual"></a>C.67: 多态类应当抑制公开的移动/复制操作

### <a name="Rc-eq-base"></a>C.87: 请当心基类的 `==`

### <a name="Rh-domain"></a>C.120: 使用类层次来表达具有天然层次化结构的概念

##### 理由

直接在代码中表达想法可以简化理解和维护工作。应当保证各个基类所表达的想法与全部派生类型精确匹配，并且确实找不到比使用继承所带来的紧耦合方式更好的表达方式。

当单纯使用数据成员就能搞定时请*不要*使用继承。这种情况通常意味着派生类型需要覆盖某个基类虚函数或者需要访问某个受保护成员。

##### 示例

    class DrawableUIElement {
    public:
        virtual void render() const = 0;
        // ...
    };

    class AbstractButton : public DrawableUIElement {
    public:
        virtual void onClick() = 0;
        // ...
    };

    class PushButton : public AbstractButton {
        void render() const override;
        void onClick() override;
        // ...
    };

    class Checkbox : public AbstractButton {
    // ...
    };

##### 示例，不好

请*不要*把非层次化的领域概念表示成类层次。

    template<typename T>
    class Container {
    public:
        // 列表操作：
        virtual T& get() = 0;
        virtual void put(T&) = 0;
        virtual void insert(Position) = 0;
        // ...
        // 向量操作：
        virtual T& operator[](int) = 0;
        virtual void sort() = 0;
        // ...
        // 树操作：
        virtual void balance() = 0;
        // ...
    };

大多数派生类都无法恰当实现这个接口所要求的大多数函数。
因而这个基类成为了一个实现负担。
此外，`Container` 的使用者无法依靠成员函数来相当高效地确实实施某个有意义的操作；
它可能会抛出某个异常。
因此使用者只得诉诸于运行时检查，并且
放弃使用这个（过于）一般化的接口，代之以某种运行时类型查询（比如 `dynamic_cast`）所确定的接口。

##### 强制实施

* 寻找带有许多不干别的只会抛出异常的成员的类。
* 对非公用基类 `B` 的每次使用进行标记，其中派生类 `D` 并未覆盖 `B` 的某个虚函数，或访问某个受保护成员，而 `B` 并非以下情况：为空，为 `D` 的模板参数或参数包组，或者为以 `D` 所特化的类模板。

### <a name="Rh-separation"></a>C.122: 当需要完全区分接口和实现时，应当用抽象类作为接口

##### 理由

诸如在 ABI（连接）边界这种地方。

##### 示例

    struct Device {
        virtual ~Device() = default;
        virtual void write(span<const char> outbuf) = 0;
        virtual void read(span<char> inbuf) = 0;
    };

    class D1 : public Device {
        // ... 数据 ...

        void write(span<const char> outbuf) override;
        void read(span<char> inbuf) override;
    };

    class D2 : public Device {
        // ... 不同的数据 ...

        void write(span<const char> outbuf) override;
        void read(span<char> inbuf) override;
    };

使用者可以通过由 `Device` 所提供的接口来互换地使用 `D1` 和 `D2`。
而且，只要其访问一直是通过 `Device` 进行的话，也可以以与老版本二进制不兼容的方式来更新 `D1` 和 `D2`。

### <a name="Rh-copy"></a>C.130: 多态类的深拷贝；优先采用虚函数 `clone` 来替代公开复制构造/赋值

##### 理由

由于切片的问题，不鼓励多态类的复制操作，参见 [C.67](#Rc-copy-virtual)。如果确实需要复制语义的话，应当进行深复制：提供一个虚 `clone` 函数，它复制的是真正的最终派生类型，并返回指向新对象的具有所有权的指针，而且在派生类中它返回的也是派生类型（利用协变返回类型）。

##### 示例

    class B {
    public:
        B() = default;
        virtual ~B() = default;
        virtual gsl::owner<B*> clone() const = 0;
    protected:
         B(const B&) = default;
         B& operator=(const B&) = default;
         B(B&&) = default;
         B& operator=(B&&) = default;
        // ...
    };

    class D : public B {
    public:
        gsl::owner<D*> clone() override
        {
            return new D{*this};
        }
    };

通常来说，推荐使用智能指针来表示所有权（参见 [R.20](#Rr-owner)）。不过根据语言规则，协变返回类型不能是智能指针：当 `B::clone` 返回 `unique_ptr<B>` 时 `D::clone` 不能返回 `unique_ptr<D>`。因此，你得在所有覆盖函数中统一都返回 `unique_ptr<B>`，或者也可以使用[指导方针支持库](#SS-views)中的 `owner<>` 工具类。

### <a name="Rh-dynamic_cast"></a>C.146: 当无法避免在类层次上进行导航时应使用 `dynamic_cast`

##### 理由

`dynamic_cast` 是运行时检查。

##### 示例

    struct B {   // 接口
        virtual void f();
        virtual void g();
        virtual ~B();
    };

    struct D : B {   // 更宽的接口
        void f() override;
        virtual void h();
    };

    void user(B* pb)
    {
        if (D* pd = dynamic_cast<D*>(pb)) {
            // ... 使用 D 的接口 ...
        }
        else {
            // ... 通过 B 的接口做事 ...
        }
    }

使用其他的强制转换可能会违反类型安全，导致程序中所访问的某个真实类型为 `X` 的变量，被当做具有某个无关的类型 `Z` 而进行访问：

    void user2(B* pb)   // 不好
    {
        D* pd = static_cast<D*>(pb);    // I know that pb really points to a D; trust me
        // ... 使用 D 的接口 ...
    }

    void user3(B* pb)    // 不安全
    {
        if (some_condition) {
            D* pd = static_cast<D*>(pb);   // I know that pb really points to a D; trust me
            // ... 使用 D 的接口 ...
        }
        else {
            // ... 通过 B 的接口做事 ...
        }
    }

    void f()
    {
        B b;
        user(&b);   // OK
        user2(&b);  // 糟糕的错误
        user3(&b);  // OK，*如果*程序员已经正确检查了 some_condition 的话
    }

##### 注解

和其他强制转换一样，`dynamic_cast` 被过度使用了。
[优先使用虚函数而不是强制转换](#Rh-use-virtual)。
如果可行（无须运行时决议）并且相当便利的话，优先使用[静态多态](#???)而不是
继承层次的导航。

##### 注解

一些人会在 `typeid` 更合适的时候使用 `dynamic_cast`；
`dynamic_cast` 是一个通用的“是一个”操作，用以发现对象上的最佳接口，
而 `typeid` 是“报告对象的精确类型”操作，用以发现对象的真实类型。
后者本质上就是更简单的操作，因而应当更快一些。
后者（`typeid`）是可以在需要时进行手工模仿的（比如说，当工作在（因为某种原因）禁止使用 RTTI 的系统上），
而前者（`dynamic_cast`）要正确地实现则要困难得多。

考虑：

    struct B {
        const char* name {"B"};
        // 若 pb1->id() == pb2->id() 则 *pb1 与 *pb2 类型相同
        virtual const char* id() const { return name; }
        // ...
    };

    struct D : B {
        const char* name {"D"};
        const char* id() const override { return name; }
        // ...
    };

    void use()
    {
        B* pb1 = new B;
        B* pb2 = new D;

        cout << pb1->id(); // "B"
        cout << pb2->id(); // "D"


        if (pb1->id() == "D") {         // 貌似没问题
            D* pd = static_cast<D*>(pb1);
            // ...
        }
        // ...
    }

`pb2->id == "D"` 的结果实际上是由实现定义的。
我们加上这个是为了警告自造的 RTTI 中的危险之处。
这个代码可能可以多年正常工作，但只在不会对字符字面量进行唯一化的新机器，新编译器，或者新的连接器上失败。

当实现你自己的 RTTI 时，请当心这一点。

##### 例外

如果你所用的实现提供的 `dynamic_cast` 确实很慢的话，你可能只得使用一种替代方案了。
不过，所有无法静态决议的替代方案都涉及显式的强制转换（通常为 `static_cast`），而且易于出错。
你基本上都将会创建自己的特殊目的 `dynamic_cast`。
因此，首先应当确定你的 `dynamic_cast` 确实和你想的一样慢（其实有相当多的并不被支持的流言），
而且你使用的 `dynamic_cast` 确实是性能十分关键的。

我们的观点是，当前的实现中的 `dynamic_cast` 并非很慢。
比如说，在合适的条件下，是可以以[快速常量时间](http://www.stroustrup.com/fast_dynamic_casting.pdf)来实施 `dynamic_cast` 的。
但是，兼容性问题使得作出改变很难，虽然大家都同意对优化付出的努力是值得的。

在很罕见的情况下，如果你已经测量出 `dynamic_cast` 的开销确实有影响，你也有其他的方式来静态地保证向下转换的成功（比如说小心地应用 CRTP 时），而且其中并不涉及虚继承的话，可以考虑战术性地使用 `static_cast` 并带上显著的代码注释和免责声明，概述这个段落，而且由于类型系统无法验证其正确性而在维护中需要人工的关切。即便是这样，以我们的经验来说，这种“我知道我在干什么”的情况仍然是一种已知的 BUG 来源。

##### 例外

考虑：

    template<typename B>
    class Dx : B {
        // ...
    };

##### 强制实施

* 对所有用 `static_cast` 来进行向下转换进行标记，其中也包括实施 `static_cast` 的 C 风格的强制转换。
* 本条规则属于[类型安全性剖面配置](#Pro-type-downcast)。

### <a name="Rh-ref-cast"></a>C.147: 当查找所需类的失败被当做一种错误时，应当对引用类型使用 `dynamic_cast`

##### 理由

对引用进行的强制转换，所表达的意图是最终会获得一个有效对象，因此这种强制转换必须成功。如果无法成功的话，`dynamic_cast` 将会抛出异常。

##### 示例

    std::string f(Base& b)
    {
        return dynamic_cast<Derived&>(b).to_string();
    }

### <a name="Rh-ptr-cast"></a>C.148: 当查找所需类的失败被当做一种有效的可能情况时，应当对指针类型使用 `dynamic_cast`

##### 理由

`dynamic_cast` 转换允许测试指针是否指向某个其类层次中包含给定类的多态对象。由于其找不到类时仅会返回空值，因而可以在运行时予以测试。这允许编写的代码可以基于其结果而选择不同的代码路径。

与此相对，[C.147](#Rh-ref-cast) 中失败即是错误，而且不能用于条件执行。

##### 示例

下面的例子的 `Shape_owner` 的 `add` 函数获取构造的 `Shape` 对象的所有权。这些对象也根据其几何特性被存储到了不同视图中。
这个例子中的 `Shape` 并不继承于 `Geometric_attributes`，而是其各个子类继承。

    void add(Shape * const item)
    {
      // 总是获得其所有权
      owned_shapes.emplace_back(item);

      // 检查 Geometric_attribute 并将该形状加入到（零个/一个/某些/全部）视图中

      if (auto even = dynamic_cast<Even_sided*>(item))
      {
        view_of_evens.emplace_back(even);
      }

      if (auto trisym = dynamic_cast<Trilaterally_symmetrical*>(item))
      {
        view_of_trisyms.emplace_back(trisym);
      }
    }

##### 注解

找不到所需的类时 `dynamic_cast` 将返回空值，而解引用空指针将导致未定义的行为。
因此 `dynamic_cast` 的结果应当总是当做可能包含空值并进行测试。

##### 强制实施

* 【复杂】 除非在指针类型 `dynamic_cast` 的结果上进行了空值测试，否则就对该指针的解引用给出警告。

### <a name="Rh-array"></a>C.152: 禁止把指向派生类对象的数组的指针赋值给指向基类的指针

##### 理由

对所得到的基类指针进行下标操作，将导致无效的对象访问并且可能造成内存损坏。

##### 示例

    struct B { int x; };
    struct D : B { int y; };

    void use(B*);

    D a[] = {{1, 2}, {3, 4}, {5, 6}};
    B* p = a;     // 不好: a 退化为 &a[0]，并被转换为 B*
    p[1].x = 7;   // 覆盖了 a[0].y

    use(a);       // 不好: a 退化为 &a[0]，并被转换为 B*

##### 强制实施

* 对任何的数组退化和基类向派生类转换之间的组合进行标记。
* 应当将数组作为 `span` 而不是指针来进行传递，而且不能让数组的名字在放入 `span` 之前经手派生类向基类的转换。

### <a name="Rh-use-virtual"></a>C.153: 优先采用虚函数而不是强制转换

### <a name="Ro-conventional"></a>C.160: 定义运算符应当主要用于模仿传统用法

##### 理由

最小化意外情况。

##### 示例

    class X {
    public:
        // ...
        X& operator=(const X&); // 定义赋值的成员函数
        friend bool operator==(const X&, const X&); // == 需要访问其内部表示
                                                    // 执行 a = b 之后将有 a == b
        // ...
    };

这里维持了传统的语义：[副本之间相等](#SS-copy)。

##### 示例，不好

    X operator+(X a, X b) { return a.v - b.v; }   // 不好: 让 + 执行减法

##### 注解

非成员运算符应当要么是友元，要么定义于[其操作数所在的命名空间中](#Ro-namespace)。
[二元运算符应当等价地对待其两个操作数](#Ro-symmetric)。

##### 强制实施

也许是不可能的。

### <a name="Ro-conversion"></a>C.164: 避免隐式转换运算符

### <a name="Ro-address-of"></a>C.166: 一元 `&` 的重载只能作为某个智能指针或引用系统的一部分而提供

##### 理由

`&` 运算符在 C++ 中很基本。
C++ 语义中的很多部分都假定了其默认的含义。

##### 示例

    class Ptr { // 一种智能指针
        Ptr(X* pp) : p(pp) { /* 检查 */ }
        X* operator->() { /* 检查 */ return p; }
        X operator[](int i);
        X operator*();
    private:
        T* p;
    };

    class X {
        Ptr operator&() { return Ptr{this}; }
        // ...
    };

##### 注解

如果你要“折腾”运算符 `&` 的话，请保证其定义和 `->`，`[]`，`*` 和 `.` 在结果类型上具有匹配的含义。
注意，运算符 `.` 现在是无法重载的，因此不可能做出一个完美的系统。
我们打算修正这一点： [Operator Dot (R2)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4477.pdf)。
注意 `std::addressof()` 总会产生一个内建指针。

##### 强制实施

比较微妙。如果用户定义了 `&` 而并未同时为其结果类型定义 `->`，则进行警告。

### <a name="Ro-overload"></a>C.167: 应当为带有传统含义的操作提供运算符

##### 理由

可读性。约定。可重用性。支持泛型代码。

##### 示例

    void cout_my_class(const My_class& c) // 含糊，并非传统约定，非泛型
    {
        std::cout << /* 此处为类成员 */;
    }

    std::ostream& operator<<(std::ostream& os, const my_class& c) // OK
    {
        return os << /* 此处为类成员 */;
    }

对于其自身而言，`cout_my_class` 也许是没问题的，但它无法用在（或组合到）依赖于 `<<` 的输出用法约定代码之中：

    My_class var { /* ... */ };
    // ...
    cout << "var = " << var << '\n';

##### 注解

大多数运算符都有很强烈和活跃的含义约定用法，比如

* 比较：`==`，`!=`，`<`，`<=`，`>`，`>=`，以及 `<=>`
* 算术操作：`+`，`-`，`*`，`/`，以及 `%`
* 访问操作：`.`，`->`，一元 `*`，以及 `[]`
* 赋值：`=`

### <a name="Renum-oper"></a>Enum.4: 针对安全和简单的用法来为枚举定义操作

##### 示例

    enum Day { mon, tue, wed, thu, fri, sat, sun };

    Day& operator++(Day& d)
    {
        return d = (d == Day::sun) ? Day::mon : static_cast<Day>(static_cast<int>(d)+1);
    }

    Day today = Day::sat;
    Day tomorrow = ++today;

这里使用 `static_cast` 有点不好，但

    Day& operator++(Day& d)
    {
        return d = (d == Day::sun) ? Day::mon : Day(++d);    // 错误
    }

是无限递归，而且不用强制转换而使用一个针对所有情况的 `switch` 太冗长了。


##### 强制实施

对重复出现的强制转换回枚举的表达式进行标记。

### <a name="Rr-ptr"></a>R.3: 原生指针（`T*`）没有所有权

##### 理由

对此（C++ 标准中和大多数代码中都）没有异议，大多数原生指针都是无所有权的。
我们希望将有所有权的指针标示出来，以使得可以可靠和高效地删除由有所有权指针所指向的对象。

##### 示例

    void f()
    {
        int* p1 = new int{7};           // 不好: 原生指针拥有了所有权
        auto p2 = make_unique<int>(7);  // OK: int 被一个唯一指针所拥有
        // ...
    }

`unique_ptr` 保证对它的对象进行删除（即便是发生异常时也如此），以此保护不发生泄漏。而 `T*` 做不到这点。

##### 示例

    template<typename T>
    class X {
    public:
        T* p;   // 不好: 不清楚 p 是不是带有所有权
        T* q;   // 不好: 不清楚 q 是不是带有所有权
        // ...
    };

可以通过明确所有权来修正这个问题：

    template<typename T>
    class X2 {
    public:
        owner<T*> p;  // OK: p 具有所有权
        T* q;         // OK: q 没有所有权
        // ...
    };

##### 注解

`owner<T*>` 并没有超出 `T*` 的默认语义。使用它可以不改动任何使用方代码，也不会影响 ABI。
它只不过是一项针对程序员和分析工具的提示。
比如说，当 `owner<T*>` 是某个类的成员时，这个类最好提供一个析构函数来 `delete` 它。

##### 示例，不好

返回（原生）指针的做法向调用方暴露了在生存期管理上的不确定性；就是说，谁应该删除其所指向的对象呢？

    Gadget* make_gadget(int n)
    {
        auto p = new Gadget{n};
        // ...
        return p;
    }

    void caller(int n)
    {
        auto p = make_gadget(n);   // 要记得 delete p
        // ...
        delete p;
    }

除了遭受[资源泄漏](#???)的问题外，这也带来了一组假性的分配和回收操作，而这其实是不必要的。如果 Gadget 可以廉价地从函数转移出来（就是说，它很小，或者具有高效的移动操作）的话，直接“按值”返回即可（参见[输出返回值](#Rf-out)）：

    Gadget make_gadget(int n)
    {
        Gadget g{n};
        // ...
        return g;
    }

##### 注解

这条规则适用于工厂函数。

##### 注解

如果指针语义是必须的（比如说，因为返回类型需要指代类层次中的基类（或接口）），则可以返回“智能指针”。

##### 强制实施

* 【简单】 对在并非 `owner<T>` 的原生指针上进行的 `delete` 给出警告。
* 【中等】 对一个 `owner<T>` 指针，当并非每个代码路径中都要么进行 `reset` 要么明确 `delete`，则给出警告。
* 【简单】 当 `new` 的返回值被赋值给原生指针时，给出警告。
* 【简单】 当函数所返回的对象是在函数中所分配的，并且它具有移动构造函数时，给出警告。
  建议代之以按值返回。

### <a name="Rr-ref"></a>R.4: 原生引用（`T&`）没有所有权

##### 理由

对此（C++ 标准中和大多数代码中都）没有异议，大多数原生引用都是无所有权的。
我们希望将所有者都标示出来，以使得可以可靠和高效地删除由有所有权指针所指向的对象。

##### 示例

    void f()
    {
        int& r = *new int{7};  // 不好: 原生的具有所有权的引用
        // ...
        delete &r;             // 不好: 违反了有关删除原生指针的规则
    }

### <a name="Rr-newdelete"></a>R.11: 避免显式调用 `new` 和 `delete`

### <a name="Rr-weak_ptr"></a>R.24: 使用 `std::weak_ptr` 来打断 `shared_ptr` 的循环引用

##### 强制实施

??? 可能无法做到。如果能够静态地检测出循环引用的话，我们就不需要 `weak_ptr` 了。

### <a name="Rr-sharedptrparam-const"></a>R.36: `const shared_ptr<widget>&` 参数用以表达它可能将保留一个对对象的引用 ???

##### 理由

这样做明确了函数的 ??? 语义。

##### 示例，好

    void share(shared_ptr<widget>);            // 共享——“将会”保持一个引用计数

    void reseat(shared_ptr<widget>&);          // “可能”重新置位指针

    void may_share(const shared_ptr<widget>&); // “可能”保持一个引用计数

##### 强制实施

* 【简单】 如果函数以左值引用接受 `Shared_pointer<T>` 参数，但并未在至少一个代码路径中向其赋值或者对其调用 `reset()`，则给出警告。建议代之以接受 `T*` 或 `T&`。
* 【简单】〔基础〕 如果函数按值或者以 `const` 引用接受 `Shared_pointer<T>` 参数，但并未在至少一个代码路径中将其复制或移动给另一个 `Shared_pointer`，则给出警告。建议代之以接受 `T*` 或 `T&`。
* 【简单】〔基础〕 如果函数以右值引用接受 `Shared_pointer<T>` 参数，则给出警告。建议代之以按值传递。

### <a name="Res-abstr"></a>ES.2: 优先采用适当的抽象而不是直接使用语言功能特性

##### 理由

“适当的抽象”（比如程序库或者类），更加贴近应用的概念而不是语言概念，将带来更简洁的代码，而且更容易进行测试。

##### 示例

    vector<string> read1(istream& is)   // 好
    {
        vector<string> res;
        for (string s; is >> s;)
            res.push_back(s);
        return res;
    }

与之近乎等价的更传统且更低层的代码，更长、更混乱、更难编写正确，而且很可能更慢：

    char** read2(istream& is, int maxelem, int maxstring, int* nread)   // 不好：啰嗦而且不完整
    {
        auto res = new char*[maxelem];
        int elemcount = 0;
        while (is && elemcount < maxelem) {
            auto s = new char[maxstring];
            is.read(s, maxstring);
            res[elemcount++] = s;
        }
        nread = &elemcount;
        return res;
    }

一旦添加了溢出检查和错误处理，代码就变得相当混乱了，而且还有个要记得 `delete` 其所返回的指针以及数组所包含的 C 风格字符串的问题。

##### 强制实施

并不容易。??? 寻找混乱的循环，嵌套的循环，长函数，函数调用的缺失，缺乏使用非内建类型。圈复杂度？

### <a name="Rconc-raii"></a>CP.20: 使用 RAII，绝不使用普通的 `lock()`/`unlock()`

### <a name="Rconc-lock"></a>CP.21: 用 `std::lock()` 或 `std::scoped_lock` 来获得多个 `mutex`

### <a name="Rconc-unknown"></a>CP.22: 绝不在持有锁的时候调用未知的代码（比如回调） -> 死锁

### <a name="Rconc-join"></a>CP.23: 把联结的 `thread` 看作是有作用域的容器

##### 强制实施

确保 `joining_thread` 不会 `detach()`。
之后，可以实施（针对局部对象的）常规的生存期和所有权强制实施方案。

### <a name="Rconc-detach"></a>CP.24: 把 `thread` 看作是全局的容器

##### 理由

为了维护指针安全性并避免泄漏，需要考虑 `thread` 所使用的指针。
如果 `thread` 脱离了，我们只可以安全地把指向静态和自由存储的对象的指针传递给它。

##### 示例

    void f(int* p)
    {
        // ...
        *p = 99;
        // ...
    }

    int glob = 33;

    void some_fct(int* p)
    {
        int x = 77;
        std::thread t0(f, &x);           // 不好
        std::thread t1(f, p);            // 不好
        std::thread t2(f, &glob);        // OK
        auto q = make_unique<int>(99);
        std::thread t3(f, q.get());      // 不好
        // ...
        t0.detach();
        t1.detach();
        t2.detach();
        t3.detach();
        // ...
    }

这里的“OK”表明对象能够在 `thread` 可以使用指向它的指针时一直处于作用域（“存活”）。
“bad”则表示 `thread` 可能在对象销毁之后使用指向它的指针。
`thread` 运行的并发性并不会影响这里的生存期或所有权问题；
这些 `thread` 可以仅仅被看成是从 `some_fct` 中调用的函数对象。

##### 注解

如果你[不 `detach()`](#Rconc-detached_thread) 并[使用 `gsl::joining_tread`](#Rconc-joining_thread) 的话，本条规则是多余的。
不过，将代码转化为遵循这些指导方针可能很困难，而对于第三方库来说更是不可能的。
这些情况下，这条规则对于生存期安全性和类型安全性来说就是必要的了。


一般来说是无法确定是否对某个 `thread` 执行了 `detach()` 的，但简单的常见情况则易于检测出来。
如果无法证明某个 `thread` 并没有 `detach()` 的话，我们只能假定它确实脱离了，且它的存活将超过其构造时所处于的作用域；
之后，可以实施（针对全局对象的）常规的生存期和所有权强制实施方案。

##### 强制实施

当试图将局部变量传递给可能 `detach()` 的线程时进行标记。

### <a name="Rconc-detached_thread"></a>CP.26: 不要 `detach()` 线程

##### 理由

通常，需要存活超出线程创建的作用域的情况是来源于 `thread` 的任务所决定的，
但用 `detach` 来实现这点将造成更加难于对脱离的线程进行监控和通信。
特别是，要确保线程按预期完成或者按预期的时间存活变得更加困难（虽然不是不可能）。

##### 示例

    void heartbeat();

    void use()
    {
        std::thread t(heartbeat);             // 不联结；打算持续运行 heartbeat
        t.detach();
        // ...
    }

这是一种合理的线程用法，一般会使用 `detach()`。
但这里有些问题。
我们怎么监控脱离的线程以查看它是否存活呢？
心跳里边可能会出错，而在需要心跳的系统中，心跳丢失可能是非常严重的问题。
因此，我们需要与心跳线程进行通信
（例如，通过某个消息流，或者使用 `condition_variable` 的通知事件）。

一种替代的，而且通常更好的方案是，通过将其放入某个其创建点（或激活点）之外的作用域来控制其生存期。
例如：

    void heartbeat();

    gsl::joining_thread t(heartbeat);             // 打算持续运行 heartbeat

这个心跳，（除非出错或者硬件故障等情况）将在程序运行时一直运行。

有时候，我们需要将创建点和所有权点分离开：

    void heartbeat();

    unique_ptr<gsl::joining_thread> tick_tock {nullptr};

    void use()
    {
        // 打算在 tick_tock 存活期间持续运行 heartbeat
        tick_tock = make_unique(gsl::joining_thread, heartbeat);
        // ...
    }

##### 强制实施

标记 `detach()`。


### <a name="Rconc-data-by-value"></a>CP.31: 少量数据在线程之间按值传递，而不是通过引用或指针传递

### <a name="Rconc-shared"></a>CP.32: 用 `shared_ptr` 在无关的 `thread` 之间共享所有权

### <a name="Rconc-wait"></a>CP.42: 不要无条件地 `wait`

### <a name="Rconc-time"></a>CP.43: 最小化临界区的时间耗费

##### 理由

获取 `mutex` 时耗费的时间越短，其他 `thread` 不得不等待的机会就会越少，
而 `thread` 的挂起和恢复是昂贵的。

##### 示例

    void do_something() // 不好
    {
        unique_lock<mutex> lck(my_lock);
        do0();  // 预备：不需要锁定
        do1();  // 事务：需要锁定
        do2();  // 清理：不需要锁定
    }

这里我们持有的锁定比所需的要长：
我们不应该在必须锁定之前就获取锁定，而且应当在开始清理之前将其释放掉。
可以将其重写为：

    void do_something() // 不好
    {
        do0();  // 预备：不需要锁定
        my_lock.lock();
        do1();  // 事务：需要锁定
        my_lock.unlock();
        do2();  // 清理：不需要锁定
    }

但这样损害了安全性并且违反了[使用 RAII](#Rconc-raii) 规则。
我们可以为临界区添加语句块：

    void do_something() // OK
    {
        do0();  // 预备：不需要锁定
        {
            unique_lock<mutex> lck(my_lock);
            do1();  // 事务：需要锁定
        }
        do2();  // 清理：不需要锁定
    }

##### 强制实施

一般来说是不可能的。
对“裸” `lock()` 和 `unlock()` 进行标记。

### <a name="Rconc-name"></a>CP.44: 记得为 `lock_guard` 和 `unique_lock` 命名

##### 理由

无名的局部对象时临时对象，会立刻离开作用域。

##### 示例

    unique_lock<mutex>(m1);
    lock_guard<mutex> {m2};
    lock(m1, m2);

这个貌似足够有效，但其实并非如此。

##### 强制实施

标记所有的无名 `lock_guard` 和 `unique_lock`。

### <a name="Rconc-mutex"></a>CP.50: `mutex` 要和其所保护的数据一起定义，只要可能就使用 `synchronized_value<T>`

##### 理由

对于读者来说，数据应该且如何被保护应当是显而易见的。这可以减少锁定错误的互斥体，或者互斥体未能被锁定的机会。

使用 `synchronized_value<T>` 保证了数据都带有互斥体，并且当访问数据时锁定正确的互斥体。
参见向某个未来的 TS 或 C++ 标准的修订版添加 `synchronized_value` [WG21 提案](http://wg21.link/p0290)。

##### 示例

    struct Record {
        std::mutex m;   // 访问其他成员之前应当获取这个 mutex
        // ...
    };

    class MyClass {
        struct DataRecord {
           // ...
        };
        synchronized_value<DataRecord> data; // 用互斥体保护数据
    };

### <a name="Rcoro-capture"></a>CP.51: 不要使用作为协程的有俘获 lambda 表达式

##### 理由

对于普通 lambda 来说正确的使用模式，对于协程 lambda 来说是高危的。很明显的变量俘获模式将会造成在首个挂起点之后访问已释放的内存，即便是带引用计数的智能指针和可复制类型也是如此。

lambda 表达式会产生一个带有存储的闭包对象，它通常在运行栈上，并会在某个时刻离开作用域。当闭包对象离开作用域时，它所俘获的也会离开作用域。普通 lambda 的执行在这个时间点都已经完成了，因此这并不是问题。闭包 lambda 则可能会在闭包对象已经销毁之后从挂起中恢复执行，而在这时其所有俘获都将变为“释放后使用”的内存访问。

##### 示例，不好

    int value = get_value();
    std::shared_ptr<Foo> sharedFoo = get_foo();
    {
      const auto lambda = [value, sharedFoo]() -> std::future<void>
      {
        co_await something();
        // "sharedFoo" 和 "value" 已被销毁
        // “共享”指针没有带来任何好处
      };
      lambda();
    } // lambda 闭包对象此时已离开作用域

##### 示例，更好

    int value = get_value();
    std::shared_ptr<Foo> sharedFoo = get_foo();
    {
      const auto lambda = [](auto sharedFoo, auto value) -> std::future<void>  // 以按值传参代替作为俘获
      {
        co_await something();
        // sharedFoo 和 value 此时仍然有效
      };
      lambda(sharedFoo, value); 
    } // lambda 闭包对象此时已离开作用域

##### 示例，最佳

使用函数作为协程。

    std::future<void> Class::do_something(int value, std::shared_ptr<Foo> sharedFoo)
    {
      co_await something();
      // sharedFoo 和 value 此时仍然有效
    }

    void SomeOtherFunction()
    {
      int value = get_value();
      std::shared_ptr<Foo> sharedFoo = get_foo();
      do_something(value, sharedFoo); 
    }

##### 强制实施

标记作为协程且具有非空俘获列表的 lambda 表达式。


### <a name="Rcoro-locks"></a>CP.52: 不要在持有锁或其它同步原语时跨越挂起点

##### 理由

这种模式会导致明显的死锁风险。某些种类的等待允许当前线程在异步操作完成前实施一些额外的工作。如果持有锁的线程实施了需要相同的所的工作，那它就会因为试图获取它已经持有的锁而发生死锁。

如果协程在某个与获得所的线程不同的另一个线程中完成，那就是未定义行为。即使协程中明确返回其原来的线程，仍然有可能在协程恢复之前抛出异常，并导致其锁定防护对象（lock guard）未能销毁。

##### 示例，不好

    std::mutex g_lock;

    std::future<void> Class::do_something()
    {
        std::lock_guard<std::mutex> guard(g_lock);
        co_await something(); // 危险：在持有锁时挂起协程
        co_await somethingElse();
    }

##### 示例，好

    std::mutex g_lock;

    std::future<void> Class::do_something()
    {
        {
            std::lock_guard<std::mutex> guard(g_lock);
            // 修改被锁保护的数据
        }
        co_await something(); // OK：锁已经在协程挂起前被释放
        co_await somethingElse();
    }


##### 注解

这种模式对于性能也不好。每当遇到比如 `co_await` 这样的挂起点时，都会停止当前函数的执行而去运行别的代码。而在协程恢复之前可能会经过很长时间。这个锁会在整个时间段中持有，并且无法被其他线程获得以进行别的工作。

##### 强制实施

标记所有未能在协程挂起前销毁的锁定防护。

### <a name="Rcoro-reference-parameters"></a>CP.53: 协程的形参不能按引用传递

##### 理由

一旦协程到达其第一个如 `co_await` 这样的挂起点，其同步执行的部分就会返回。这个位置之后，所有按引用传递的形参都是悬挂引用。此后对它们的任何使用都是未定义行为，可能包括向已释放的内存进行写入。

##### 示例，不好

    std::future<int> Class::do_something(const std::shared_ptr<int>& input)
    {
        co_await something();

        // 危险：对 input 的引用可能不再有效，可能已经是已释放内存
        co_return *input + 1;
    }

##### 示例，好

    std::future<int> Class::do_something(std::shared_ptr<int> input)
    {
        co_await something();
        co_return *input + 1; // input 是一个副本，且到此处仍有效
    }

##### 注解

这个问题并不适用于仅在第一个挂起点之前访问的引用形参。此后对函数的改动中可能会添加或移除挂起点，而这可能会再次引入这一类的缺陷。一些种类的协程，在协程执行第一行代码之前就会有挂起点，这种情况中的引用形参总是不安全的。一直采用按值传递的方式更安全，因为所复制的形参存活于协程的栈帧中，并在整个协程中都可以安全访问。

##### 注解

输出参数也有这种危险。[F.20: 对于“输出（out）”值，采用返回值优先于输出参数](#Rf-out) 不建议使用输出参数。协程应当完全避免输出参数。

##### 强制实施

标记协程的所有引用形参。

### <a name="Rconc-double"></a>CP.110: 不要为初始化编写你自己的双检查锁定

##### 理由

从 C++11 开始，静态局部变量是以线程安全的方式初始化的。当和 RAII 模式结合时，静态局部变量可以取代为初始化自己编写双检查锁定的需求。`std::call_once` 也可以达成相同的目的。请使用 C++11 的静态局部变量或者 `std::call_once` 来代替自己为初始化编写的双检查锁定。

##### 示例

使用 `std::call_once` 的例子。

    void f()
    {
        static std::once_flag my_once_flag;
        std::call_once(my_once_flag, []()
        {
            // 这个只做一次
        });
        // ...
    }

使用 C++11 的线程安全静态局部变量的例子。

    void f()
    {
        // 假定编译器遵循 C++11
        static My_class my_object; // 构造函数仅调用一次
        // ...
    }

    class My_class
    {
    public:
        My_class()
        {
            // 这个只做一次
        }
    };

##### 强制实施

??? 是否可能检测出这种惯用法？

### <a name="Rconc-double-pattern"></a>CP.111: 当确实需要双检查锁定时应当采用惯用的模式

##### 理由

双检查锁定是很容易被搞乱的。如果确实需要编写自己的双检查锁定，而不顾规则 [CP.110: 不要为初始化编写你自己的双检查锁定](#Rconc-double)和规则 [CP.100: 除非绝对必要，请勿使用无锁编程](#Rconc-lockfree)，那么应当采用惯用的模式。

使用双检查锁定模式而不违反[CP.110: 不要为初始化编写你自己的双检查锁定](#Rconc-double)的情形，出现于当某个非线程安全的动作既困难也罕见，并且存在某个快速且线程安全的测试可以用于保证该动作并不需要实施的情况，但反过来的情况则无法保证。

##### 示例，不好

使用 `volatile` 并不能使得第一个检查线程安全，另见[CP.200: `volatile` 仅用于和非 C++ 内存进行通信](#Rconc-volatile2)

    mutex action_mutex;
    volatile bool action_needed;

    if (action_needed) {
        std::lock_guard<std::mutex> lock(action_mutex);
        if (action_needed) {
            take_action();
            action_needed = false;
        }
    }

##### 示例，好

    mutex action_mutex;
    atomic<bool> action_needed;

    if (action_needed) {
        std::lock_guard<std::mutex> lock(action_mutex);
        if (action_needed) {
            take_action();
            action_needed = false;
        }
    }

这对于正确调校的内存顺序可能会带来好处，其中的获取加载要比顺序一致性加载更加高效

    mutex action_mutex;
    atomic<bool> action_needed;

    if (action_needed.load(memory_order_acquire)) {
        lock_guard<std::mutex> lock(action_mutex);
        if (action_needed.load(memory_order_relaxed)) {
            take_action();
            action_needed.store(false, memory_order_release);
        }
    }

##### 强制实施

??? 是否可能检测出这种惯用法？

### <a name="Rconc-volatile2"></a>CP.200: `volatile` 仅用于和非 C++ 内存进行通信

##### 理由

`volatile` 用于涉指那些与“非 C++”代码之间共享的对象，或者不遵循 C++ 内存模型的硬件。

##### 示例

    const volatile long clock;

这说明了一个被某个时钟电路不断更新的寄存器。
`clock` 为 `volatile` 是因为其值将会在没有使用它的 C++ 程序的任何动作下被改变。
例如，两次读取 `clock` 经常会产生两个不同的值，因此优化器最好不要将下面代码中的第二个读取操作优化掉：

    long t1 = clock;
    // ... 这里没有对 clock 的使用 ...
    long t2 = clock;

`clock` 为 `const` 是因为程序不应当试图写入 `clock`。

##### 注解

除非你是在编写直接操作硬件的最底层代码，否则应当把 `volatile` 当做是某种深奥的功能特性并最好避免使用。

##### 示例

通常 C++ 代码接受的 `volatile` 内存是由别处所拥有的（硬件或其他语言）：

    int volatile* vi = get_hardware_memory_location();
        // 注意：我们获得了指向别人的内存的指针
        // volatile 说明“请特别尊重地对待”

有时候 C++ 代码会分配 `volatile` 内存，并通过故意地暴露一个指针来将其共享给“别人”（硬件或其他语言）：

    static volatile long vl;
    please_use_this(&vl);   // 暴露对这个的一个引用给“别人”（不是 C++）

##### 示例，不好

`volatile` 局部变量几乎都是错误的——既然是短暂的，它们如何才能共享给其他语言或硬件呢？
因为相同的理由，这几乎同样强有力地适用于成员变量。

    void f()
    {
        volatile int i = 0; // 不好，volatile 局部变量
        // etc.
    }

    class My_type {
        volatile int i = 0; // 可以的，volatile 成员变量
        // etc.
    };

##### 注解

于其他一些语言不通，C++ 中的 `volatile` [和同步没有任何关系](#Rconc-volatile)。

##### 强制实施

* 对 `volatile T` 的局部成员变量进行标记；几乎肯定你应当用 `atomic<T>` 进行代替。

### <a name="Re-finally"></a>E.19: 当没有合适的资源包装时，使用 `final_action` 对象来表达清理动作

##### 理由

[GSL](#S-gsl) 提供的 `finally` 要比 `try`/`catch` 更不啰嗦且难于搞错。

##### 示例

    void f(int n)
    {
        void* p = malloc(n);
        auto _ = gsl::finally([p] { free(p); });
        // ...
    }

##### 注解

`finally` 没有 `try`/`catch` 那样混乱，但它仍然比较专门化。
优先采用[适当的资源管理对象](#Re-raii)。
万不得已考虑使用 `finally`。

##### 注解

相对于老式的 [`goto exit;` 技巧](#Re-no-throw-codes)来说，使用 `finally` 是处理并非系统化的资源管理中的清理工作的
更加系统化并且相当简洁的方案。

##### 强制实施

启发式措施：检测 `goto exit;`。

### <a name="Re-no-throw-codes"></a>E.27: 当不能抛出异常时，系统化地使用错误代码

### <a name="Rt-algo"></a>T.2: 用模板来表达适用于许多参数类型的算法

##### 理由

通用性。最小化源代码数量。互操作性。重用。

##### 示例

这正是 STL 的基础所在。一个 `find` 算法可以很轻易地同任何输入范围一起工作：

    template<typename Iter, typename Val>
        // requires Input_iterator<Iter>
        //       && Equality_comparable<Value_type<Iter>, Val>
    Iter find(Iter b, Iter e, Val v)
    {
        // ...
    }

##### 注解

除非确实需要多于一种模板参数类型，否则请不要使用模板。
请勿过度抽象。

### <a name="Rt-low"></a>T.20: 避免没有有意义的语义的“概念”

##### 理由

概念是用于表现语义的观念的，比如“数”，元素的“范围”，以及“全序的”等等。
简单的约束，比如“带有 `+` 运算符”和“带有 `>` 运算符”，是无法独立进行有意义的运用的，
而仅应当被用作有意义的概念的构造块，而不是在用户代码中使用。

##### 示例，不好

    template<typename T>
    // 不好，不充分
    concept Addable = requires(T a, T b) { a+b; };

    template<Addable N>
    auto algo(const N& a, const N& b) // 使用两个数值
    {
        // ...
        return a + b;
    }

    int x = 7;
    int y = 9;
    auto z = algo(x, y);   // z = 16

    string xx = "7";
    string yy = "9";
    auto zz = algo(xx, yy);   // zz = "79"

也许拼接是有意进行的。不过更可能的是一种意外。而对减法进行同等的定义则会导致可接受类型的集合的非常不同。
这个 `Addable` 违反了加法应当可交换的数学法则：`a+b == b+a`。

##### 注解

给出有意义的语义的能力，在于定义真正的概念的特征，而不是仅给出语法约束。

##### 示例

    template<typename T>
    // 假定数值的运算符 +、-、* 和 / 都遵循常规的数学法则
    concept Number = requires(T a, T b) { a+b; a-b; a*b; a/b; };

    template<Number N>
    auto algo(const N& a, const N& b)
    {
        // ...
        return a + b;
    }

    int x = 7;
    int y = 9;
    auto z = algo(x, y);   // z = 16

    string xx = "7";
    string yy = "9";
    auto zz = algo(xx, yy);   // 错误：string 不是 Number

##### 注解

带有多个操作的概念要远比单个操作的概念更少和类型发生意外匹配的机会。

##### 强制实施

* 对在其他 `concept` 的定义之外使用的但操作 `concept` 进行标记。
* 对表现为模拟单操作 `concept` 的 `enable_if` 的使用进行标记。

### <a name="Rt-refine"></a>T.23: 通过添加新的使用模式，从更一般情形的概念中区分出提炼后的概念

##### 理由

否则编译器是无法自动对它们进行区分的。

##### 示例

    template<typename I>
    // 注：<iterator> 中定义了 input_iterator
    concept Input_iter = requires(I iter) { ++iter; };

    template<typename I>
    // 注：<iterator> 中定义了 forward_iterator
    concept Fwd_iter = Input_iter<I> && requires(I iter) { iter++; };

编译器可以基于所要求的操作的集合（这里为前缀 `++`）来确定提炼关系。
这样做减少了这些类型的实现者的负担，
因为他们不再需要任何特殊的声明来“打入概念内部”了。
如果两个概念具有完全相同的要求的话，它们在逻辑上就是等价的（不存在提炼）。

##### 强制实施

* 对与已经出现的另一个概念具有完全相同的要求的概念进行标记（它们中不存在更精炼的概念）。
  为对它们进行区分，参见 [T.24](#Rt-tag)。

### <a name="Rt-tag"></a>T.24: 用标签类或特征类来区分仅在语义上存在差别的概念

##### 理由

要求相同的语法但具有不同语义的两个概念之间会造成歧义，除非程序员对它们进行区分。

##### 示例

    template<typename I>    // 提供随机访问的迭代器
    // 注：<iterator> 中定义了 random_access_iterator
    concept RA_iter = ...;

    template<typename I>    // 提供对连续数据的随机访问的迭代器
    // 注：<iterator> 中定义了 contiguous_iterator
    concept Contiguous_iter =
        RA_iter<I> && is_contiguous_v<I>;  // 使用 is_contiguous 特征

程序员（在程序库中）必须适当地定义（特征） `is_contiguous`。

把标签类包装到概念中可以得到这个方案的更简单的表达方式：

    template<typename I> concept Contiguous = is_contiguous_v<I>;

    template<typename I>
    concept Contiguous_iter = RA_iter<I> && Contiguous<I>;

程序员（在程序库中）必须适当地定义（特征） `is_contiguous`。

##### 注解

特征可以是特征类或者类型特征。
它们可以是用户定义的，或者标准库中的。
优先采用标准库中的特征。

##### 强制实施

* 编译器会将对相同的概念的有歧义的使用标记出来。
* 对相同的概念定义进行标记。

### <a name="Rt-use"></a>T.26: 优先采用使用模式而不是简单的语法来定义概念

##### 理由

其定义更可读，而且更直接地对应于用户需要编写的代码。
其中同时兼顾了类型转换。你再不需要记住所有的类型特征的名字。

##### 示例

你可能打算这样来定义概念 `Equality`：

    template<typename T> concept Equality = has_equal<T> && has_not_equal<T>;

显然，直接使用标准的 `equality_comparable` 要更好而且更容易，
但是——只是一个例子——如果你不得不定义这样的概念的话，应当这样：

    template<typename T> concept Equality = requires(T a, T b) {
        { a == b } -> std::convertible_to<bool>;
        { a != b } -> std::convertible_to<bool>;
        // axiom { !(a == b) == (a != b) }
        // axiom { a = b; => a == b }  // => 的意思是“意味着”
    };

而不是定义两个无意义的概念 `has_equal` 和 `has_not_equal` 仅用于帮助 `Equality` 的定义。
“无意义”的意思是我们无法独立地指定 `has_equal` 的语义。

### <a name="Rt-deduce"></a>T.44: （如果可行）使用函数模板来对类模板的参数类型进行推断

##### 理由

显式写出模板参数类型既麻烦又无必要。

##### 示例

    tuple<int, string, double> t1 = {1, "Hamlet", 3.14};   // 明确类型
    auto t2 = make_tuple(1, "Ophelia"s, 3.14);         // 更好；推断类型

注意这里用 `s` 后缀来确保字符串是 `std::string` 而不是 C 风格字符串。

##### 注解

既然你可以轻易写出 `make_T` 函数，编译器也可以。以后 `make_T` 函数也许将会变得多余。

##### 例外

有时候没办法对模板参数进行推断，而有时候你则想要明确指定参数：

    vector<double> v = { 1, 2, 3, 7.9, 15.99 };
    list<Record*> lst;

##### 注解

注意，C++17 强允许模板参数直接从构造函数参数进行推断，而使这条规则变得多余：
[构造函数的模板形参推断(Rev. 3)](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0091r1.html)。
例如：

    tuple t1 = {1, "Hamlet"s, 3.14}; // 推断为：tuple<int, string, double>

##### 强制实施

当显式指定的类型与所使用的类型精确匹配时进行标记。

### <a name="Rt-concept-def"></a>T.48: 如果你的编译器不支持概念的话，可以用 `enable_if` 来模拟

##### 理由

因为这是我们没有直接的概念支持时能够做到的最好的方式。
`enable_if` 可被用于有条件地定义函数，以及用于在一组函数中进行选择。

##### 示例

    template<typename T>
    enable_if_t<is_integral_v<T>>
    f(T v)
    {
        // ...
    }

    // 等价于：
    template<Integral T>
    void f(T v)
    {
        // ...
    }

##### 注解

请当心[互补约束](#Rt-not)。
当用 `enable_if` 来模拟概念重载时，有时候会迫使我们使用这种易错的设计技巧。

### <a name="Rt-scary"></a>T.61: 请勿对成员进行过度参数化（SCARY）

##### 理由

不依赖于模板参数的成员，除非给定某个特定的模板参数，否则也是无法使用的。
这样会限制其使用，而且通常会增加代码大小。

##### 示例，不好

    template<typename T, typename A = std::allocator<T>>
        // requires Regular<T> && Allocator<A>
    class List {
    public:
        struct Link {   // 并未依赖于 A
            T elem;
            Link* pre;
            Link* suc;
        };

        using iterator = Link*;

        iterator first() const { return head; }

        // ...
    private:
        Link* head;
    };

    List<int> lst1;
    List<int, My_allocator> lst2;

这看起来没什么问题，但现在 `Link` 形成依赖于分配器（尽管它不使用分配器）。 这迫使冗余的实例化在某些现实场景中可能造成出奇的高的成本。
通常，解决方案是使用自己的最小模板参数集使嵌套类非局部化。

    template<typename T>
    struct Link {
        T elem;
        Link* pre;
        Link* suc;
    };

    template<typename T, typename A = std::allocator<T>>
        // requires Regular<T> && Allocator<A>
    class List2 {
    public:
        using iterator = Link<T>*;

        iterator first() const { return head; }

        // ...
    private:
        Link<T>* head;
    };

    List2<int> lst1;
    List2<int, My_allocator> lst2;

人们发现 `Link` 不再隐藏在列表中很可怕，所以我们命名这个技术为 [SCARY](http://www.open-std.org/jtc1/sc22/WG21/docs/papers/2009/n2911.pdf)。
引自该学术论文：“首字母缩略词 SCARY 描述了看似错误的赋值和初始化（受冲突的通用参数的约束），
但实际上使用了正确的实现（由于最小化的依赖而不受冲突的约束）。”

##### 注解

这同样适用于那些并不依赖于其全部模板形参的 lambda 表达式。

##### 强制实施

* 对并未依赖于全部模板形参的成员类型进行标记。
* 对并未依赖于全部模板形参的成员函数进行标记。
* 对并未依赖于全部模板形参的 lambda 表达式或变量模板进行标记。

### <a name="Rt-tag-dispatch"></a>T.65: 用标签分派来提供函数的其他实现

##### 理由

* 模板定义了通用接口。
* 标签派发允许我们基于参数类型的特定性质选择不同的实现。
* 性能。

##### 示例

这是 `std::copy` 的一个简化版本（忽略了非连续序列的可能性）

    struct pod_tag {};
    struct non_pod_tag {};

    template<class T> struct copy_trait { using tag = non_pod_tag; };   // T 不是“朴素数据”

    template<> struct copy_trait<int> { using tag = pod_tag; };         // int 是“朴素数据”

    template<class Iter>
    Out copy_helper(Iter first, Iter last, Iter out, pod_tag)
    {
        // 使用 memmove
    }

    template<class Iter>
    Out copy_helper(Iter first, Iter last, Iter out, non_pod_tag)
    {
        // 使用调用复制构造函数的循环
    }

    template<class Iter>
    Out copy(Iter first, Iter last, Iter out)
    {
        return copy_helper(first, last, out, typename copy_trait<Iter>::tag{})
    }

    void use(vector<int>& vi, vector<int>& vi2, vector<string>& vs, vector<string>& vs2)
    {
        copy(vi.begin(), vi.end(), vi2.begin()); // 使用 memmove
        copy(vs.begin(), vs.end(), vs2.begin()); // 使用调用复制构造函数的循环
    }

这是一种进行编译时算法选择的通用且有力的技巧。

##### 注解

当可以广泛使用 `concept` 之后，这样的替代实现就可以直接进行区分了：

    template<class Iter>
        requires Pod<Value_type<iter>>
    Out copy_helper(In, first, In last, Out out)
    {
        // 使用 memmove
    }

    template<class Iter>
    Out copy_helper(In, first, In last, Out out)
    {
        // 使用调用复制构造函数的循环
    }

### <a name="Rt-customization"></a>T.69: 在模板中，请勿进行未限定的非成员函数调用，除非有意将之作为定制点

##### 理由

* 仅提供预计之内的灵活性。
* 避免源于意外的环境改变的威胁。

##### 示例

主要有三种方法使调用代码对模板进行定制化。

    template<class T>
        // 调用成员函数
    void test1(T t)
    {
        t.f();    // 要求 T 提供 f()
    }

    template<class T>
    void test2(T t)
        // 不带限定地调用非成员函数
    {
        f(t);     // 要求 f(/*T*/) 在调用方的作用域或者 T 的命名空间中可用
    }

    template<class T>
    void test3(T t)
        // 调用一个“特征”
    {
        test_traits<T>::f(t); // 要求定制化 test_traits<>
                              // 以获得非默认的函数和类型
    }

特征通常是用以计算一个类型的类型别名，
用以计算一个值的 `constexpr` 函数，
或者针对用户的类型进行特化的传统的特征模板。

##### 注解

当你打算为依赖于某个模板类型参数的值 `t` 调用自己的辅助函数 `helper(t)` 时，
请将函数放入一个 `::detail` 命名空间中，并把调用限定为 `detail::helper(t);`。
无限定的调用将成为一个定制点，它将会调用处于 `t` 的类型所在命名空间中的任何 `helper` 函数；
这可能会导致诸如[意外地调用了无约束函数模板](#Rt-visible)这样的问题。

##### 强制实施

* 在模板中，如果非成员函数的无限定调用传递了具有依赖类型的变量，而在该模板的命名空间中存在相同名字的非成员函数，则对其进行标记。

### <a name="Rt-hier"></a>T.80: 请勿不成熟地对类层次进行模板化

##### 理由

使一个带有许多函数，尤其是有许多虚函数的类层次进行模板化，会导致代码膨胀。

##### 示例，不好

    template<typename T>
    struct Container {         // 这是一个接口
        virtual T* get(int i);
        virtual T* first();
        virtual T* next();
        virtual void sort();
    };

    template<typename T>
    class Vector : public Container<T> {
    public:
        // ...
    };

    Vector<int> vi;
    Vector<string> vs;

把 `sort` 定义为容器的成员函数可能是一个比较糟糕的主意，不过这样做并不鲜见，而且它是一个展示不应当做的事情的好例子。

在这之中，编译器不知道 `Vector<int>::sort()` 是不是会被调用，因此它必须为之生成代码。
`Vector<string>::sort()` 也与此相似。
除非这两个函数被调用，否则这就是代码爆炸。
不难想象当一个带有几十个成员函数和几十个派生类的类层次被大量实例化时会怎么样。

##### 注解

许多情况下都可以通过不为基类进行参数化而提供一个稳定的接口；
参见[“稳定的基类”](#Rt-abi)和 [OO 与 GP](#Rt-generic-oo)。

##### 强制实施

* 对依赖于模板参数的虚函数进行标记。 ??? 误报

### <a name="Rt-array"></a>T.81: 请勿混合类层次和数组

##### 理由

派生类的数组可以隐式地“退化”成指向基类的指针，并带来潜在的灾难性后果。

##### 示例

假定 `Apple` 和 `Pear` 是两种 `Fruit`。

    void maul(Fruit* p)
    {
        *p = Pear{};     // 把一个 Pear 放入 *p
        p[1] = Pear{};   // 把一个 Pear 放入 p[1]
    }

    Apple aa [] = { an_apple, another_apple };   // aa 包含的是 Apple （显然！）

    maul(aa);
    Apple& a0 = &aa[0];   // 是 Pear 吗？
    Apple& a1 = &aa[1];   // 是 Pear 吗？

`aa[0]` 可能会变为 `Pear`（并且没进行过强制转换！）。
当 `sizeof(Apple) != sizeof(Pear)` 时，对 `aa[1]` 的访问就是并未跟数组中的对象的适当起始位置进行对齐的。
这里出现了类型违例，以及很可能出现的内存损坏。
决不要写这样的代码。

注意，`maul()` 违反了 [`T*` 应指向独立对象的规则](#Rf-ptr)。

**替代方案**: 使用适当的（模板化）容器：

    void maul2(Fruit* p)
    {
        *p = Pear{};   // 把一个 Pear 放入 *p
    }

    vector<Apple> va = { an_apple, another_apple };   // va 包含的是 Apple （显然！）

    maul2(va);       // 错误: 无法把 vector<Apple> 转换为 Fruit*
    maul2(&va[0]);   // 这是你明确要做的

    Apple& a0 = &va[0];   // 是 Pear 吗？

注意，`maul2()` 中的赋值违反了[避免发生切片的规则](#Res-slice)。

##### 强制实施

* 对这种恐怖的东西进行检测！

### <a name="Rt-virtual"></a>T.83: 请勿声明虚的成员函数模板(模板类不能为虚)

### <a name="Rt-abi"></a>T.84: 使用非模板的核心实现来提供 ABI 稳定的接口

##### 理由

提升代码的稳定性。
避免代码爆炸。

##### 示例

这个应当是基类：

    struct Link_base {   // 稳定
        Link_base* suc;
        Link_base* pre;
    };

    template<typename T>   // 模板化的包装带来了类型安全性
    struct Link : Link_base {
        T val;
    };

    struct List_base {
        Link_base* first;   // 第一个元素（如果有）
        int sz;             // 元素数量
        void add_front(Link_base* p);
        // ...
    };

    template<typename T>
    class List : List_base {
    public:
        void put_front(const T& e) { add_front(new Link<T>{e}); }   // 隐式强制转换为 Link_base
        T& front() { static_cast<Link<T>*>(first).val; }   // 显式强制转换回 Link<T>
        // ...
    };

    List<int> li;
    List<string> ls;

这样的话就只有一份用于对 `List` 的元素进行入链和解链的操作的代码了。
而类 `Link` 和 `List` 除了进行类型操作之外什么也没做。

除了使用一个独立的“base”类型外，另一种常用的技巧是对 `void` 或 `void*` 进行特化，并让针对 `T` 的通用模板成为在从或向 `void` 的核心实现进行强制转换的一层类型安全封装。

**替代方案**: 使用一个 [PImpl](#Ri-pimpl) 实现。x

## <a name="SS-meta"></a>T.meta: 模板元编程（TMP）

模板提供了一种编译期编程的通用机制。

元编程，是其中至少一项输入或者一项输出是类型的编程。
模板提供了编译期的图灵完备（除了内存消耗外）的鸭子类型系统。
其语法和所需技巧都相当可怕。

### <a name="Rt-metameta"></a>T.120: 仅当确实需要时才使用模板元编程

##### 理由

模板元编程很难做对，它会拖慢编译速度，而且通常很难维护。
不过，现实世界有些例子中模板元编程提供了比其他专家级的汇编代码替代方案还要更好的性能。
而且，也存在现实世界的例子用模板元编程做到比运行时代码更好地表达基本设计意图的情况。
例如，当确实需要在编译期进行 AST 操作时，（比如说对矩阵操作进行可选的折叠），C++ 中可能没有其他的实现方式。

##### 示例，不好

    enable_if

请使用概念来替代它。不过请参见[如何在没有语言支持时模拟概念](#Rt-emulate)。


**替代方案**: 如果结果是一个值而不是类型，请使用 [`constexpr` 函数](#Rt-fct)。

##### 注解

当你觉得需要把模板元编程代码隐藏到宏之中时，你可能已经跑得太远了。

### <a name="Rt-emulate"></a>T.121: 模板元编程主要用于模拟概念机制

##### 理由

不能使用 C++20 时，我们需要用 TMP 来模拟它。
对概念给出要求的用例（比如基于概念进行重载）是 TMP 的最常见（而且最简单）的用法。

##### 示例

    template<typename Iter>
        /*requires*/ enable_if<random_access_iterator<Iter>, void>
    advance(Iter p, int n) { p += n; }

    template<typename Iter>
        /*requires*/ enable_if<forward_iterator<Iter>, void>
    advance(Iter p, int n) { assert(n >= 0); while (n--) ++p;}

##### 注解

这种代码使用概念时将更加简单：

    void advance(random_access_iterator auto p, int n) { p += n; }

    void advance(forward_iterator auto p, int n) { assert(n >= 0); while (n--) ++p;}

### <a name="Rt-std-tmp"></a>T.124: 优先使用标准库的模板元编程设施

##### 理由

标准中所定义的设施，诸如 `conditional`，`enable_if`，以及 `tuple` 等，是可移植的，可以假定为大家所了解。

### <a name="Rt-nongeneric"></a>T.143: 请勿编写并非有意非泛型的代码

##### 理由

一般性。可重用性。请勿无必要地陷入技术细节之中；请使用最广泛可用的设施。

##### 示例

用 `!=` 而不是 `<` 来比较迭代器；`!=` 可以在更多对象上正常工作，因为它并未蕴含有序性。

    for (auto i = first; i < last; ++i) {   // 通用性较差
        // ...
    }

    for (auto i = first; i != last; ++i) {   // 好; 通用性较强
        // ...
    }

当然，范围式 `for` 在符合需求的时候当然是更好的选择。

##### 示例

使用能够提供所需功能的最接近基类的类。

    class Base {
    public:
        Bar f();
        Bar g();
    };

    class Derived1 : public Base {
    public:
        Bar h();
    };

    class Derived2 : public Dase {
    public:
        Bar j();
    };

    // 不好，除非确实有特别的原因来将之仅限制为 Derived1 对象
    void my_func(Derived1& param)
    {
        use(param.f());
        use(param.g());
    }

    // 好，仅使用 Base 的接口，且保证了这个类型
    void my_func(Base& param)
    {
        use(param.f());
        use(param.g());
    }

##### 强制实施

* 对使用 `<` 而不是 `!=` 的迭代器比较进行标记。
* 当存在 `x.empty()` 或 `x.is_empty()` 时，对 `x.size() == 0` 进行标记。`empty()` 比 `size()` 能够对于更多的容器工作，因为某些容器是不知道自己的大小的，甚至概念上就是大小无界的。
* 如果函数接受指向更加派生的类型的指针或引用，但仅使用了在某个基类中所声明的函数，则对其进行标记。

### <a name="Rstr-view"></a>SL.str.2: 使用 `std::string_view` 或 `gsl::span<char>` 以指代字符序列

##### 理由

`std::string_view` 或 `gsl::span<char>` 提供了简易且（潜在）安全的对字符序列的访问，并与序列的
分配和存储方式无关。

##### 示例

    vector<string> read_until(string_view terminator);

    void user(zstring p, const string& s, string_view ss)
    {
        auto v1 = read_until(p);
        auto v2 = read_until(s);
        auto v3 = read_until(ss);
        // ...
    }

##### 注解

`std::string_view`（C++17）是只读的。

### <a name="Rstr-span"></a>SL.str.11: 当需要改动字符串时，使用 `gsl::span<char>` 而不是 `std::string_view`

##### 理由

`std::string_view` 是只读的。

##### 强制实施

编译器会标记出试图写入 `string_view` 的地方。

### <a name="Rstr-s"></a>SL.str.12: 为作为标准库的 `string` 类型的字符串字面量使用后缀 `s`

##### 理由

直接表达想法能够最小化犯错机会。

##### 示例

    auto pp1 = make_pair("Tokyo", 9.00);         // {C 风格字符串,double} 有意如此？
    pair<string, double> pp2 = {"Tokyo", 9.00};  // 稍微啰嗦
    auto pp3 = make_pair("Tokyo"s, 9.00);        // {std::string,double}    // C++14
    pair pp4 = {"Tokyo"s, 9.00};                 // {std::string,double}    // C++17

### <a name="Rio-low"></a>SL.io.1: 仅在必要时才使用字符层面的输入

##### 理由

除非你确实仅处理单个的字符，否则使用字符级的输入将导致用户代码实施潜在易错的
且潜在低效的从字符进行标记组合的工作。

##### 示例

    char c;
    char buf[128];
    int i = 0;
    while (cin.get(c) && !isspace(c) && i < 128)
        buf[i++] = c;
    if (i == 128) {
        // ... 处理过长的字符串 ....
    }

更好的做法（简单得多而且可能更快）：

    string s;
    s.reserve(128);
    cin>>s;

而且额能并不需要 `reserve(128)`。

##### 讨论：`iostream` vs. `printf()` 家族

人们通常说（并且通常是正确的）`printf` 家族比 `iostream` 有两个优势：
格式化的灵活性和性能。
这需要与 `iostream` 在处理用户定义类型方面的扩展性，针对安全性的违反方面的韧性，
隐含的内存管理，以及 `locale` 处理等优势之间进行权衡。

如果需要 I/O 性能的话，你几乎总能做到比 `printf()` 更好。

`gets()`，使用 `%s` 的 `scanf()`，和使用 `%s` 的 `printf()` 在安全性方面冒风险（容易遭受缓冲区溢出问题而且通常很易错）。
C11 定义了一些“可选扩展”，它们对其实参进行一些额外检查。
如果您的 C 程序库中包含 `gets_s()`、`scanf_s()` 和 `printf_s()`，它们也许是更安全的替代方案，但仍然并非是类型安全的。

##### 强制实施

可选地标记 `<cstdio>` 和 `<stdio.h>`。

### <a name="Rio-sync"></a>SL.io.10: 除非你使用了 `printf` 族函数，否则要调用 `ios_base::sync_with_stdio(false)`

##### 理由

`iostreams` 和 `printf` 风格的 I/O 之间的同步是由代价的。
`cin` 和 `cout` 默认是与 `printf` 相同步的。

##### 示例

    int main()
    {
        ios_base::sync_with_stdio(false);
        // ... 使用 iostreams ...
    }

## <a name="SS-lifetime"></a>Pro.lifetime: 生存期安全性剖面配置

通过已经不指向任何东西的指针进行访问，是错误的一种主要来源，
而且在许多传统的 C 或 C++ 风格的编程中这很难避免。
例如，指针可能未初始化，值为 `nullptr`，指向越过指针范围，或者指向已删除的对象。

[参见此处的设计说明书的当前版本](https://github.com/isocpp/CppCoreGuidelines/blob/master/docs/Lifetime.pdf)

生存期安全性剖面配置概览：

* <a name="Pro-lifetime-invalid-deref"></a>Lifetime.1: 不要解引用无效指针：
[检测或避免](#Res-deref)。

##### 影响

一旦强制实施了编码风格规则，静态分析，以及程序库支持的组合方案之后，本剖面配置将能

* 消除 C++ 中的恶劣错误的一种主要来源
* 消除潜在安全漏洞的一种主要来源
* 通过消除多余的“偏执”检查而改善性能
* 提升代码正确性的信心
* 通过强制遵循一种关键的 C++ 语言规则而避免未定义的行为

## <a name="SS-views"></a>GSL.view: 视图

这些类型使用户可以区分带有和没有所有权的指针，并区分指向单个对象的指针和指向序列的第一个元素的指针。

“视图”都不是所有者。

引用都不是所有者（参见 [R.4](#Rr-ref)）。注意：有许多机会能让引用存活超过其所指代的对象，如按引用返回局部变量，持有 vector 的某个元素的引用然后进行 `push_back`，绑定到  `std::max(x, y + 1)`，等等。生存期安全性剖面配置的目标就是处理这些事情，但即便如此 `owner<T&>` 也没有意义且不建议使用。

它们的名字基本上遵循 ISO 标准库风格（小写字母和下划线）：

* `T*`      // `T*` 不是所有者，可能为 null；假定为指向单个元素。
* `T&`      // `T&` 不是所有者，不可能为“null 引用”；引用总是绑定到对象上。

“原生指针”写法（如 `int*`）假定为具有其最常见的含义；亦即指向一个对象的指针，但并不拥有它。
所有者应当被转换为资源包装（如 `unique_ptr` 或 `vector<T>`），或标为 `owner<T*>`。

* `owner<T*>`   // `T*`，拥有所指向/指代的对象；可能为 `nullptr`。

`owner` 用于对代码中有所有权的指针进行标记，它们无法更改为使用适当的资源包装。
其原因可能包括：

* 转换的成本。
* 需要为某个 ABI 使用指针。
* 这个指针时某种资源包装的实现的一部分。

`owner<T>` 和 `T` 的某种资源包装的区别在于它仍然需要明确进行 `delete`。

`owner<T>` 假定为指代自由存储（堆）上的某个对象。

当某个东西不应当为 `nullptr` 时，可以这样做：

* `not_null<T>`   // `T` 通常是某个指针类型（例如 `not_null<int*>` 和 `not_null<owner<Foo*>>`），且不能为 `nullptr`。
  `T` 可以是 `==nullptr` 有意义的任何类型。

* `span<T>`       // `[p:p+n)`，构造函数接受 `{p, q}` 和 `{p, n}`；`T` 为指针类型
* `span_p<T>`     // `{p, predicate}` `[p:q)`，其中 `q` 为首个使 `predicate(*p)` 为真的元素

`span<T>` 指代零或更多可改动的 `T`，除非 `T` 为 `const` 类型。

“指针算术”最好在 `span` 之内进行。
指向多个 `char` 但并非 C 风格字符串的 `char*`（比如指向某个输入缓冲区的指针）应当表示为一个 `span`。

* `zstring`    // `char*`，假定为 C 风格字符串；亦即以零结尾的 `char` 的序列或者是 `nullptr`
* `czstring`   // `const char*`，假定为 C 风格字符串；亦即以零结尾的 `const` `char` 的序列或者是 `nullptr`

逻辑上来说，最后两种别名是没有必要的，但我们并不总是依照逻辑的，它们可以在指向单个 `char` 的指针和指向 C 风格字符串的指针之间明确地进行区分。
并未假定为零结尾的字符序列应当是 `span<char>`，或当因 ABI 问题而不可能时是 `char*`，而不是 `zstring`。


对于不能为 `nullptr` 的 C 风格字符串，应使用 `not_null<zstring>`。 ??? 我们需要为 `not_null<zstring>` 命名吗？还是说它的难看是有用的？

## <a name="SS-utilities"></a>GSL.util: 工具

* `finally`        // `finally(f)` 创建一个 `final_action{f}`，其析构函数将执行 `f`
* `narrow_cast`    // `narrow_cast<T>(x)` 就是 `static_cast<T>(x)`
* `narrow`         // `narrow<T>(x)` 在满足无符号提升下的 `static_cast<T>(x) == x` 时为 `static_cast<T>(x)`，否则抛出 `narrowing_error`（例如，`narrow<unsigned>(-42)` 会抛出异常）
* `[[implicit]]`   // 放在单参数构造函数上的“记号”，以明确说明它们并非显式构造函数。
* `move_owner`     // `p = move_owner(q)` 含义为 `p = q` 但 ???
* `joining_thread` // RAII 风格版本的进行联结的 `std::thread`
* `index`          // 用于进行所有的容器和数组索引的类型（当前是 `ptrdiff_t` 的别名）

## <a name="SS-gsl-concepts"></a>GSL.concept: 概念

这些概念（类型谓词）借用于
Andrew Sutton 的 Origin 程序库，
Range 提案，
以及 ISO WG21 的 Palo Alto TR。
其中许多都与已在 C++20 中成为 ISO C++ 标准的概念十分相似。