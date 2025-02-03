/**
 * @brief Lớp WeakPointer quản lý một con trỏ không sở hữu đối tượng, dựa trên SharedPointer.
 * @tparam T Kiểu dữ liệu của đối tượng được quản lý.
 */
template <typename T>
class WeakPointer
{
private:
    T *ptr;                /**< Con trỏ thô đến đối tượng được quản lý. */
    size_t *ref_count;     /**< Bộ đếm tham chiếu. */

public:
    /**
     * @brief Constructor khởi tạo WeakPointer từ SharedPointer.
     * @param shared Đối tượng SharedPointer.
     */
    WeakPointer(const SharedPointer<T> &shared) : ptr(shared.get()), ref_count(nullptr)
    {
        ref_count = shared.use_count() ? new size_t(shared.use_count()) : nullptr;
    }

    /**
     * @brief Destructor giải phóng tài nguyên nếu cần.
     */
    ~WeakPointer()
    {
        if (ref_count && --(*ref_count) == 0)
        {
            delete ref_count;
        }
    }

    /**
     * @brief Kiểm tra xem WeakPointer có còn quản lý đối tượng không.
     * @return true nếu đối tượng không tồn tại, false ngược lại.
     */
    bool expired() const
    {
        return !ref_count || *ref_count == 0;
    }

    /**
     * @brief Chuyển WeakPointer thành SharedPointer nếu đối tượng còn tồn tại.
     * @return SharedPointer đến đối tượng hoặc SharedPointer trống nếu đối tượng không còn tồn tại.
     */
    SharedPointer<T> lock() const
    {
        return expired() ? SharedPointer<T>(nullptr) : SharedPointer<T>(ptr);
    }
};


int main()
{
    SharedPointer<int> sp1(new int(100));
    cout << "sp1 value: " << *sp1 << ", ref count: " << sp1.use_count() << endl;

    SharedPointer<int> sp2 = sp1;
    cout << "sp2 value: " << *sp2 << ", ref count: " << sp1.use_count() << endl;

    sp1 = SharedPointer<int>(new int(200));
    cout << "sp1 new value: " << *sp1 << ", ref count: " << sp1.use_count() << endl;
    cout << "sp2 value: " << *sp2 << ", ref count: " << sp2.use_count() << endl;

    WeakPointer<int> wp(sp2);
    cout << "wp expired: " << wp.expired() << endl;

    if (!wp.expired())
    {
        SharedPointer<int> sp3 = wp.lock();
        cout << "sp3 value: " << *sp3 << ", ref count: " << sp3.use_count() << endl;
    }

    return 0;
}
