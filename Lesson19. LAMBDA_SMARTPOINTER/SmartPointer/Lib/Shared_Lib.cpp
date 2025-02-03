#include <iostream>
#include <algorithm>

using namespace std;

/**
 * @brief  Lớp SharedPointer quản lý một con trỏ chung giữa nhiều đối tượng, sử dụng đếm tham chiếu để tự động giải phóng.
 * @tparam T Kiểu dữ liệu của đối tượng được quản lý.
 */
template <typename T>
class SharedPointer
{
    private:
        T *ptr;              /**< Con trỏ thô đến đối tượng được quản lý. */
        size_t *ref_count;   /**< Bộ đếm tham chiếu. */


        void release_in()
        {
            if (ref_count && --(*ref_count) == 0)
            {
                delete ptr;
                delete ref_count;
            }
        }

    public:
        /**
         * @brief Constructor khởi tạo SharedPointer.
         * @param p Con trỏ thô đến đối tượng. Giá trị mặc định là nullptr.
         */
        SharedPointer(T *p = nullptr) : ptr(p), ref_count(p ? new size_t(1) : nullptr){}


        /**
         * @brief Destructor giải phóng vùng nhớ nếu không còn tham chiếu.
         */
        ~SharedPointer()
        {
            release_in();
        }


        /**
         * @brief Copy constructor tăng bộ đếm tham chiếu.
         * @param other Đối tượng SharedPointer cần sao chép.
         */
        SharedPointer(const SharedPointer &other) : ptr(other.ptr), ref_count(other.ref_count)
        {
            if (ref_count) (*ref_count)++;
        }


        /**
         * @brief  Toán tử gán bằng copy.
         * @param  other Đối tượng SharedPointer cần sao chép.
         * @return Tham chiếu đến đối tượng SharedPointer hiện tại.
         */
        SharedPointer& operator = (const SharedPointer &other)
        {
            if (this != &other)
            {
                release();
                ptr = other.ptr;
                ref_count = other.ref_count;
                if (ref_count) (*ref_count)++;
            }
            return *this;
        }
        // shared1 = new int(10);
        // shared2 = new int(20); 
        // shared2 = shared1


        /**
         * @brief Move constructor chuyển nhượng quyền sở hữu.
         * @param other Đối tượng SharedPointer cần chuyển nhượng.
         */
        SharedPointer(SharedPointer &&other) noexcept : ptr(other.ptr), ref_count(other.ref_count)
        {
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }


        /**
         * @brief  Toán tử gán bằng move.
         * @param  other Đối tượng SharedPointer cần chuyển nhượng.
         * @return Tham chiếu đến đối tượng SharedPointer hiện tại.
         */
        SharedPointer& operator = (SharedPointer &&other) noexcept
        {
            if (this != &other)
            {
                release();

                this->ptr = other.ptr;
                this->ref_count = other.ref_count;
                
                other.ptr = nullptr;
                other.ref_count = nullptr;
            }
            return *this;
        }


        /**
         * @brief  Toán tử dereference để truy cập đối tượng được quản lý.
         * @return Tham chiếu đến đối tượng được quản lý.
         */
        T& operator * () const
        {
            return *ptr;
        }


        /**
         * @brief  Toán tử để truy cập thành phần của đối tượng được quản lý.
         * @return Con trỏ đến đối tượng được quản lý.
         */
        T* operator -> () const
        {
            return ptr;
        }


        /**
         * @brief  Lấy con trỏ thô đến đối tượng được quản lý.
         * @return Con trỏ thô đến đối tượng.
         */
        T* get() const
        {
            return ptr;
        }


        /**
         * @brief   Giải phóng đối tượng hiện tại và quản lý đối tượng mới.
         * @param   p   Con trỏ thô đến đối tượng mới. Mặc định là nullptr.
         */
        void reset(T *newPtr = nullptr)
        {

            release();
            ptr = newPtr;
            ref_count = newPtr ? new size_t(1) : nullptr;
        }


        /**
         * @brief  Giải phóng tài nguyên và trả về con trỏ thô hiện tại.
         * @return Con trỏ thô đến đối tượng được quản lý trước khi giải phóng.
         */
        T* release()
        {
            T *temp = ptr;
            ptr = nullptr;
            if (ref_count && --(*ref_count) == 0)
            {
                delete ref_count;
                ref_count = nullptr;
            }
            return temp;
        }


        /**
         * @brief  Lấy số lượng tham chiếu hiện tại.
         * @return Số lượng tham chiếu.
         */
        size_t use_count() const
        {
            return ref_count ? (*ref_count) : 0;
        }

        /**
         * @brief  Kiểm tra xem SharedPointer có đang quản lý đối tượng không.
         * @return true nếu không quản lý đối tượng, false ngược lại.
         */
        bool unique() const
        {
            return use_count() == 1;
        }
};


/**
 * @brief  Lớp WeakPointer quản lý một con trỏ không sở hữu đối tượng, dựa trên SharedPointer.
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
         * @brief  Kiểm tra xem WeakPointer có còn quản lý đối tượng không.
         * @return true nếu đối tượng không tồn tại, false ngược lại.
         */
        bool expired() const
        {
            return !ref_count || *ref_count == 0;
        }


        /**
         * @brief  Chuyển WeakPointer thành SharedPointer nếu đối tượng còn tồn tại.
         * @return SharedPointer đến đối tượng hoặc SharedPointer trống nếu đối tượng không còn tồn tại.
         */
        SharedPointer<T> lock() const
        {
            return expired() ? SharedPointer<T>(nullptr) : SharedPointer<T>(ptr);
        }
};

int main()
{
    // Khởi tạo Shared Pointer 1
    SharedPointer<int> sp1 = new int(100);
    cout << "sp1 value: " << *sp1 << ", count: " << sp1.use_count() << endl;


    // Khởi tạo Shared Pointer 2 (copy constructor)
    SharedPointer<int> sp2(sp1);
    cout << "sp2 value: " << *(sp2.get()) << ", count: " << sp2.use_count() << endl;


    // Khởi tạo Shared Pointer 3 (copy assignment operator)
    SharedPointer<int> sp3, sp4;
    sp4 = sp1;
    sp3 = sp1;
    cout << "sp3 value: " << *sp3 << ", count: " << sp3.use_count() << endl;

    
    // Khởi tạo Shared Pointer 4 trong Lambda sau khi thoát khỏi hàm sẽ bị thu hồi
    {
        SharedPointer<int> sp4 = sp2;
        cout << "sp4 value: " << *sp2 << ", count: " << sp1.use_count() << endl;
    }

    // Đếm số lượng shared pointer
    cout << "count: " << sp2.use_count() << endl;


    // Shared Pointer 1 & 2 không còn quản lý đối tượng
    sp1.reset();
    sp2.reset();


    // chuyển quyền sở hữu đối tượng cho con trỏ thô mới
    int *rawPtr = sp3.release();
    cout << "raw pointer: " << *rawPtr << endl;
    cout << "count Raw Pointer: " << sp3.use_count() << endl;
    
    cout << "count: " << sp1.use_count() << endl;

    // Khởi tạo Weak Pointer
    WeakPointer<int> wp(sp4);
    cout << "wp expired: " << wp.expired() << endl;
    cout << "count: " << sp4.use_count() << endl;

    if (!wp.expired())
    {
        cout << "value after change to shared pointer: " << *(wp.lock()) <<  endl;
    }

    return 0;
}
