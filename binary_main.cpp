#include <iostream>
#include <iomanip>
#include "binary_tree.h"

void print_tree(binary_tree );
int main() {
	setlocale(LC_ALL, "Russian");
	binary_tree tree;


    int menu{ -1 };

    constexpr std::string_view str_menu[]{
        "0-�����",
        "1-����������� ������ ",
        "2-�������� ������� ",
        "3-����������� ������� ��������",
        "4-������� ����",
        "5-����� �������",
        "6-����� �������(����������)",
        "7-����� ������ ������",
        "8-������� ������",
        "9-�������� �� �������",
        "10-������ � ����",
        "11-������� �� �����"


    };

    auto print_menu = [&]() constexpr {
        for (auto&& element : str_menu) {
            std::cout << element << std::endl;

        }
    };

    auto get_file_path = []() {
        std::string file_path;
        std::cout << "������� ��� �����: ";
        std::cin >> file_path;
        return file_path;
    };

    auto enter_numb = [&](auto number) {
        std::cout << "������� �����:";
        std::cin >> number;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            throw std::exception("������ ����� ");
        }
        else {
            return number;
        }
    };

    print_menu();

    while (menu) {
        std::cout << "������� ���������: "; std::cin >> menu;
        switch (menu)
        {

        case 1:
            print_tree(tree);
            break;
        case 2:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                tree.insert(numb);

            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 3:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                tree.insert_recr(numb);
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 4:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                tree.delete_node(numb);
            }
            catch (const std::exception& e) {

                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 5:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                auto answ=tree.find_element(numb);
                if (answ)
                    std::cout << "������� ����";
                else
                    std::cout << "�������� ���";
                std::cout << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
        }
        break;
        case 6:
        {
            try {
                int numb{};
                numb = enter_numb(numb);
                auto answ = tree.find_element_recr(numb);
                if (answ)
                    std::cout << "������� ����";
                else
                    std::cout << "�������� ���";
                std::cout << std::endl;
            }
            catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
            }
          
        }
        break;
        case 7:
        {
            auto answ=tree.height();
            std::cout << answ << std::endl;

        }
        break;
        case 8:
        {
            tree.delete_tree();

        }
        break;
        case 9:
        {
            auto answ=tree.is_empty();
            if (answ) std::cout << "��p��� ������";
            else std::cout << "��p��� �� ������";
            std::cout << std::endl;


        }
        break;
        case 10:
        {
            auto file_path = get_file_path();
            tree.write_to_file(file_path);


        }
        break;
        case 11:
        {
            auto file_path = get_file_path();
            tree.read_fr_file(file_path);


        }
        break;
        case 0:
            break;

        default:
            std::cout << "������" << std::endl;
        }

    }


	

}

void print_tree(binary_tree tree) {

    if (tree.is_empty())
       std::cout<<"������ ������"<<std::endl;
    else {
        auto print_lambd = [](auto&& node) {
            std::cout << node << " ";
        };
        //this->pre_order()
        std::cout << "������ �����:" << std::endl;
        std::cout << "    �����������: ";
        tree.pre_order_recr(print_lambd);
        std::cout << std::endl;
        std::cout << std::setw(17) << "    �������: ";
        tree.pre_order(print_lambd);

        std::cout << std::endl;
        std::cout << "������������ �����:" << std::endl;
        std::cout << "    �����������: ";
        tree.in_order(print_lambd);

        std::cout << std::endl;
        std::cout << "�������� �����:" << std::endl;
        std::cout << "    �����������: ";
        tree.post_order(print_lambd);

        std::cout << std::endl;
        std::cout << "����� �� ������:" << std::endl;
        std::cout << "               : ";
        tree.bfs_order(print_lambd);
        std::cout << std::endl;
    }

}
