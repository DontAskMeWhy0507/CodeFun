def parse_functional_dependencies(input_string):
   dependencies = []
   for dependency in input_string.split(","):
       lhs, rhs = dependency.split("->")
       lhs = list(lhs.strip())
       rhs = list(rhs.strip())
       dependencies.append((lhs, rhs))
   return dependencies


def find_attribute_closure(attributes, functional_dependencies):
   closure = set(attributes)
   while True:
       old_closure = closure.copy()
       for lhs, rhs in functional_dependencies:
           if set(lhs).issubset(closure):
               closure.update(rhs)
       if old_closure == closure:
           break
   return closure


def is_equivalent(fd1, fd2, attributes):
   """
   Kiểm tra xem 2 tập phụ thuộc hàm có tương đương không.
   """
   for attr in attributes:
       closure_fd1 = find_attribute_closure([attr], fd1)
       closure_fd2 = find_attribute_closure([attr], fd2)
       if closure_fd1 != closure_fd2:
           return False
   return True


def find_candidate_key(attributes, functional_dependencies):
   candidate_key = set(attributes)
   for attr in attributes:
       temp_key = candidate_key - {attr}
       closure = find_attribute_closure(temp_key, functional_dependencies)
       if not set(attributes).issubset(closure):
           candidate_key.add(attr)
       else:
           candidate_key.discard(attr)
   return candidate_key


def find_minimal_cover(functional_dependencies):
   """
   Tìm phủ tối thiểu của tập phụ thuộc hàm.
   """
   # Bước 1: Chuẩn hóa các phụ thuộc hàm dạng X -> A1, A2, ... thành X -> A từng cái một
   minimal_cover = []
   for lhs, rhs in functional_dependencies:
       for attr in rhs:
           minimal_cover.append((lhs, [attr]))


   # Bước 2: Loại bỏ thuộc tính dư thừa ở vế trái
   for i, (lhs, rhs) in enumerate(minimal_cover):
       for attr in lhs[:]:
           temp_lhs = lhs.copy()
           temp_lhs.remove(attr)
           if is_equivalent(minimal_cover, [(temp_lhs, rhs)], lhs + rhs):
               lhs.remove(attr)


   # Bước 3: Loại bỏ các phụ thuộc hàm dư thừa
   for fd in minimal_cover[:]:
       temp_cover = minimal_cover.copy()
       temp_cover.remove(fd)
       if is_equivalent(minimal_cover, temp_cover, lhs + rhs):
           minimal_cover.remove(fd)


   return minimal_cover


if __name__ == "__main__":


   while True:
       print("\nChọn chức năng:")
       print("1. Tìm bao đóng của tập thuộc tính")
       print("2. Tìm một khóa của quan hệ")
       print("3. Kiểm tra tính tương đương giữa các tập phụ thuộc hàm")
       print("4. Tìm phủ tối thiểu của tập phụ thuộc hàm")
       print("5. Thoát chương trình")


       choice = input("Nhập số tương ứng với chức năng bạn muốn thực hiện: ").strip()


       if choice == "1":
           # Tìm bao đóng của tập thuộc tính
           attributes = input("Nhập các thuộc tính của lược đồ quan hệ (cách nhau bằng dấu phẩy): ").split(",")
           attributes = [attr.strip() for attr in attributes]
           fds = input("Nhập các phụ thuộc hàm (e.g., A->B, AB->C): ").strip()
           functional_dependencies = parse_functional_dependencies(fds)
           attribute_set = input("Nhập tập thuộc tính cần tìm bao đóng (cách nhau bằng dấu phẩy): ").split(",")
           attribute_set = [attr.strip() for attr in attribute_set]
           closure = find_attribute_closure(attribute_set, functional_dependencies)
           print(f"Bao đóng của {attribute_set} là: {closure}")
          
          


       elif choice == "2":
           # Tìm một khóa của quan hệ
           attributes = input("Nhập các thuộc tính của lược đồ quan hệ (cách nhau bằng dấu phẩy): ").split(",")
           attributes = [attr.strip() for attr in attributes]
           fds = input("Nhập các phụ thuộc hàm (e.g., A->B, AB->C): ").strip()
           functional_dependencies = parse_functional_dependencies(fds)
           candidate_key = find_candidate_key(attributes, functional_dependencies)
           print(f"Khóa của lược đồ quan hệ là: {candidate_key}")


       elif choice == "3":
           # Kiểm tra tính tương đương giữa các tập phụ thuộc hàm
           attributes = input("Nhập các thuộc tính của lược đồ quan hệ (cách nhau bằng dấu phẩy): ").split(",")
           attributes = [attr.strip() for attr in attributes]


           num_fd_sets = int(input("Nhập số lượng tập phụ thuộc hàm: "))
           fd_sets = {}


           for i in range(num_fd_sets):
               name = input(f"Nhập tên tập phụ thuộc hàm thứ {i + 1}: ").strip()
               fds = input(f"Nhập các phụ thuộc hàm trong {name} (e.g., A->B, AB->C): ").strip()
               fd_sets[name] = parse_functional_dependencies(fds)


           print("\nKiểm tra tính tương đương giữa các tập phụ thuộc hàm:")
           keys = list(fd_sets.keys())
           for i in range(len(keys)):
               for j in range(i + 1, len(keys)):
                   fd1_name, fd2_name = keys[i], keys[j]
                   if is_equivalent(fd_sets[fd1_name], fd_sets[fd2_name], attributes):
                       print(f"Tập {fd1_name} và {fd2_name} là tương đương.")
                   else:
                       print(f"Tập {fd1_name} và {fd2_name} không tương đương.")


       elif choice == "4":
           # Tìm phủ tối thiểu của tập phụ thuộc hàm
           fds = input("Nhập các phụ thuộc hàm (e.g., A->B, AB->C): ").strip()
           functional_dependencies = parse_functional_dependencies(fds)
           minimal_cover = find_minimal_cover(functional_dependencies)
           print("Phủ tối thiểu của tập phụ thuộc hàm là:")
           for lhs, rhs in minimal_cover:
               print(f"{''.join(lhs)} -> {''.join(rhs)}")


       elif choice == "5":
           # Thoát chương trình
           print("Thoát chương trình.")
           break


       else:
           print("Lựa chọn không hợp lệ. Vui lòng thử lại.")



