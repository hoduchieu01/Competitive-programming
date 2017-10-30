# USACO DEC 09 GOLD Cow Toll Path
## Hồ Đức Hiếu

## Problem Statement
 Cho 1 đồ thị có n đỉnh (1<=n<= 250), và m cạnh (m <= 10 000). Mỗi cạnh và mỗi đỉnh của đồ thị đều có giá của nó. Giá của 1 chu trình được tính bằng tổng giá của các cạnh trong chu trình cộng với giá lớn nhất của các đỉnh nó đi qua (tính cả nút bắt đầu và nút kết thúc). Cho k truy vấn (k <= 10 000), với mỗi truy vấn i hãy in ra giá nhỏ nhất để đi từ đỉnh a_i đến b_i.
## Required Skills
  Thuật toán Floyd O
## Step-by-Step Solution
Ta cần một thuật toán để tính chi phí đi lại giữa các đỉnh để tìm giá nhỏ nhất để đi qua các đỉnh. Với (1 <= N <= 250) => thuật toán tìm đường đi ngắn nhất.Floyd là thuật toán ngắn nhất ghép cặp các đường đi bằng cách thêm 1 đỉnh vào 1 đồ thị.
 * Ta thấy đường đi ngắn nhất là con đường ngắn nhất mà chỉ sử dụng một số các đỉnh của đồ thị.
 * Ý tưởng : 
 Ta sắp xếp các đỉnh theo thứ tự tăng dần theo giá của đỉnh.Tiếp đó sử dụng Floyd để kiểm tra thứ tự sắp xếp của các đỉnh trong đồ thị. Sau đó ta tìm được con đường với giá rẻ nhất và số đỉnh bằng với số đỉnh thứ i trong đồ thị. Như vậy, sau mỗi lần, chúng ta thêm giá đỉnh thứ i vào chi phí cạnh của mỗi con đường và kiểm tra xem có tìm được con đường có giá nhỏ hơn giá đã tìm được không. Con đường với giá rẻ nhất là con đường rẻ nhất của tất cả con đường tìm thấy sau mỗi lần lặp của Floyd.

## Conclusion
