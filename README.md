***** Bài tập lớn CTDLGT
****Chủ đề 12: Quản lý người dùng và dữ liệu Phòng LAB
*Các bước để cài đặt và sử dụng Code: (để sử dụng một cách mượt mà, khuyến nghị tải Microsoft VS)
    B1: Cài đặt file trong đường liên kết https://github.com/LAMCAIN/bai-tap-lon-CTDLGT/tree/main
    B2: Sau khi cài đặt xong, tiến hành mở file riel.cpp
    B3: Khởi chạy.
    B4: Cửa sổ sẽ hiện ra 4 lựa chọn với: 1. Đăng nhập; 2. Tạo user; 3. Xuất report; 4. Thoát

        Khởi đầu chương trình sẽ có sẵn 1 tài khoản với username = "admin" và password = "123". Người dùng đăng nhập với tài khoản này và bắt đầu tạo user với username, password, role; sau khi tạo có thể chọn 4 để restart chương trình rồi thử đăng nhập với user vừa tạo. Người dùng sẽ vào được và có các việc có thể làm tùy theo role của user: với role ADMIN thì có thể tạo user và xuất report; với role USER thì chỉ cso thể xuất report.


*Phân tích độ phức tạp:
    Đăng nhập: O(1)
    Tìm User: O(1)
    Tạo User: O(n)
    Xử lý Role: O(1)

*Kết quả chạy:
1. Dang nhap
2. Tao User (Chon ADMIN/USER)
3. Xuat REPORT
4. Thoat
Chon:
1
User: lam
Pass: 123
Dang nhap thanh cong!

=== QLY PHONG LAB ===
1. Dang nhap
2. Tao User (Chon ADMIN/USER)
3. Xuat REPORT
4. Thoat
Chon: 2
Username moi: truc
Pass moi: 345
Role (ADMIN ho?c USER): user
Loi: Chi ADMIN moi co quyen nay!

=== QLY PHONG LAB ===
1. Dang nhap
2. Tao User (Chon ADMIN/USER)
3. Xuat REPORT
4. Thoat
Chon: 4

