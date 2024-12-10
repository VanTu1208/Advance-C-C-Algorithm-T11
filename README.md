# Advance-C-Cpp-Algorithm-T11
## Bài 2: STDARG - ASSERT
### Thư viện STDARG
 > **Cung cấp các phương thức để làm việc với hàm có tham số đầu vào chưa xác định**

**Bao gồm:**
```cpp
va_list: Kiểu dữ liệu cho các đối tượng lưu danh sách có đối số biến đổi

va_start(v,l): Cần được gọi trước khi truy cập các đối số trong danh sách v, hoặc có chức năng tách phần tử đầu tiên l ra khỏi danh sách


va_arg(v,l): Truy cập lần lượt một đối số trong danh sách v và ép kiểu theo l

va_copy(d,s): copy danh sách s và gán vào danh sách d

va_end(v): Kết thúc việc sử dụng danh sách đối số biến đổi, được gọi trước khi kết thúc hàm.
```
