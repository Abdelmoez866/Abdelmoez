#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <cstdlib>
using namespace std;

// Data structures to store user, product, and cart information
struct user_info
{
    string username, password, role, id;
};

struct product_info
{
    string id, name, price, quantity, description, category;
};

struct cart_info
{
    string id, name, price, quantity, user;
};

// Global vectors to store all data
vector<product_info> products;
vector<user_info> users;
vector<cart_info> cart;

// Global variables for temporary storage
string username, name_of_user, password_of_user, role_of_user, id_of_user;
string name_of_product, id_of_product, price_of_product, description_of_product;
string category_of_product, quantity_of_product, line;
int option;

// Clears the console screen
void clear_screen()
{
	Sleep(300) ;
    system("Cls");
}

// Displays invalid option message
void wrong_option()
{
    cout << "Invalid option, try again\n";
}

// Prints a thin separator line
void print_thin_line()
{
    cout << "--------------------------\n";
}

// Prints a thick separator line
void print_line()
{
    cout << "==========================\n";
}

// Prompts user to select an option
void select_option()
{
    cout << "Select option: ";
    cin >> option;
}

// Waits for user input to continue
void to_next_step()
{
    cout << "Press a button to continue\n";
    _getch();
}

// Shows loading animation
void show_loading()
{
    for (int i = 1; i <= 3; i++)
    {
       Sleep(500);
        cout << '.';
    }
    cout << endl;
}

// Displays welcome screen with loading animations
void show_welcome_screen()
{
    print_line();
    cout << "  E-Commerce Simulation    \n";
    print_line();
    cout << "Welcome, Ready to start!";
	show_loading() ;
    to_next_step();
}

// Adds user data to users vector
void push_to_users()
{
    user_info info_of_user;
    info_of_user.id = id_of_user;
    info_of_user.username = username;
    info_of_user.password = password_of_user;
    info_of_user.role = role_of_user;
    users.push_back(info_of_user);
}

// Adds product data to products vector
void push_to_products()
{
    product_info info_of_product;
    info_of_product.id = id_of_product;
    info_of_product.name = name_of_product;
    info_of_product.category = category_of_product;
    info_of_product.description = description_of_product;
    info_of_product.price = price_of_product;
    info_of_product.quantity = quantity_of_product;
    products.push_back(info_of_product);
}

// Adds item to cart vector
void push_to_cart()
{
    cart_info info_of_product;
    info_of_product.id = id_of_product;
    info_of_product.name = name_of_product;
    info_of_product.price = price_of_product;
    info_of_product.quantity = quantity_of_product;
    info_of_product.user = name_of_user;
    cart.push_back(info_of_product);
}

// Loads cart data from file
void loading_cart()
{
    ifstream user("Cart.txt");
    while (getline(user, line))
    {
        if (line.empty())
        {
            continue;
        }
        stringstream ss(line);
        getline(ss, id_of_product, ',');
        getline(ss, name_of_product, ',');
        getline(ss, price_of_product, ',');
        getline(ss, quantity_of_product, ',');
        getline(ss, name_of_user);
        push_to_cart();
    }
    user.close();
}

// Loads user data from file
void loading_users()
{
    ifstream user("users.txt");
    while (getline(user, line))
    {
        if (line.empty())
        {
            continue;
        }
        stringstream ss(line);
        getline(ss, id_of_user, ',');
        getline(ss, username, ',');
        getline(ss, password_of_user, ',');
        getline(ss, role_of_user);
        push_to_users();
    }
    user.close();
}

// Loads product data from file
void loading_products()
{
    ifstream product("products.txt");
    while (getline(product, line))
    {
        if (line.empty())
        {
            continue;
        }
        stringstream ss(line);
        getline(ss, id_of_product, ',');
        getline(ss, name_of_product, ',');
        getline(ss, price_of_product, ',');
        getline(ss, quantity_of_product, ',');
        getline(ss, category_of_product, ',');
        getline(ss, description_of_product);
        push_to_products();
    }
    product.close();
}

// Adds item to cart file and vector
void add_to_cart(int ID, string quantity)
{
    ofstream product_to_cart("Cart.txt", ios::app);
    id_of_product = to_string(cart.size());
    product_to_cart << ID << ',';
    product_to_cart << products[ID].name << ',';
    product_to_cart << products[ID].price << ',';
    product_to_cart << quantity << ',' << username << "\n";
    cart_info info_of_product;
    info_of_product.id = ID;
    info_of_product.name = products[ID].name;
    info_of_product.price = products[ID].price;
    info_of_product.quantity = quantity;
    info_of_product.user = username;
    cart.push_back(info_of_product);
    product_to_cart.close();
}

// Displays detailed product information
void show_a_details_of_product(string ID)
{
	clear_screen() ;
    int product_id = stoi(ID);
    print_line();
    cout << "     Product Details     \n";
    print_line();
    cout << "ID: " << product_id << "\n";
    cout << "Name: " << products[product_id].name << "\n";
    cout << "Category: " << products[product_id].category << "\n";
    cout << "Quantity: " << products[product_id].quantity << "\n";
    cout << "Description: " << products[product_id].description << "\n";
    print_thin_line();
    cout << "[1] Add to Cart\n";
    cout << "[2] Back\n";
    select_option();
    if (option == 1)
    {
        string Q;
        cout << "Quantity of product: ";
        cin >> Q;
        if (stoi(Q) > stoi(products[product_id].quantity))
        {
            wrong_option();
            show_a_details_of_product(ID);
        }
        else
        {
            cout << "Product added to Cart!\n";
            to_next_step();
			clear_screen() ;
            add_to_cart(product_id, Q);
        }
    }
    else if (option == 2)
    {
		clear_screen() ;
        return;
    }
    else
    {
        wrong_option();
    }
}

// Displays the shopping cart contents
void view_cart()
{
    print_line();
    cout << "    Shopping Cart\n";
    print_line();
    float total = 0;
    cout << left << setw(5) << "ID" << left << setw(30) << "Name" << right << setw(10) << "Price" << right << setw(8) << "Qty\n";
    
    for (int pr = 1; pr < cart.size(); pr++)
    {
        if (cart[pr].user == username)
        {
            cout << left << setw(5) << cart[pr].id << left << setw(30) << cart[pr].name << right << setw(10) << cart[pr].price << right << setw(8) << cart[pr].quantity << "\n";
            total += stof(cart[pr].price) * stoi(cart[pr].quantity);
        }
    }
    
    cout << "Total: " << total << endl;
    cout << "[0] Back\n";
    select_option();
    
    if (option != 0)
    {
        wrong_option();
    }
}

// Displays products by category with pagination
void print_products(string category)
{
    print_line();
    cout << setw(15) << category << " Products\n";
    print_line();
    cout << left << setw(5) << "ID" << left << setw(30) << "Name" << right << setw(8) << "Price\n";
    
    int number_of_products = 0, index = 0;
    vector<int> last_pages;
    string choice;
    
    for (int pr = 0; pr < products.size(); pr++)
    {
        if (products[pr].category == category)
        {
            cout << left << setw(5) << products[pr].id << left << setw(30) << products[pr].name << right << setw(8) << products[pr].price << "\n";
            
            if (number_of_products == 0)
            {
                last_pages.push_back(pr);
            }
            number_of_products++;
        }
        
        if (number_of_products == 10)
        {
            print_thin_line();
            number_of_products = 0;
            cout << "[N] Next Page    [P] Previous Page\n";
            cout << "[B] Back \n";
            cout << "or Enter Product ID for details: ";
            cin >> choice;
            
            if (choice == "N")
            {
                clear_screen();
                index++;
                continue;
            }
            else if (choice == "P")
            {
                clear_screen();
                if (index == 0)
                {
                    pr = --last_pages[index];
                }
                else
                {
                    pr = --last_pages[--index];
                }
            }
            else if (choice == "B")
            {
                clear_screen();
                return;
            }
            else if (choice[0] >= '0' && choice[0] <= '9')
            {
                show_a_details_of_product(choice);
            }
            else
            {
                wrong_option();
                break;
            }
        }
    }
}

// Main product browsing interface
void browse_products()
{
    while (true)
    {
        print_line();
        cout << "      Browse Products\n";
        print_line();
        cout << "Select Category\n";
        cout << "[1] Technology\n";
        cout << "[2] Clothing\n";
        cout << "[3] Books\n";
        cout << "[4] Home & Kitchen\n";
        cout << "[5] Sports\n";
        cout << "[6] New\n";
        cout << "[7] Back\n";
        print_thin_line();
        select_option();
        clear_screen() ;
        if (option == 1)
        {
            print_products("Technology");
        }
        else if (option == 2)
        {
            print_products("Clothing");
        }
        else if (option == 3)
        {
            print_products("Books");
        }
        else if (option == 4)
        {
            print_products("Home&Kitchen");
        }
        else if (option == 5)
        {
            print_products("Sports");
        }
        else if (option == 6)
        {
            print_products("New");
        }
        else if (option == 7)
        {
            return;
        }
        else
        {
            wrong_option();
        }
    }
}

// Customer menu interface
void customer_menu()
{
    while (true)
    {
        print_line();
        cout << "     Customer Menu\n";
        print_line();
        cout << "[1] Browse Products\n";
        cout << "[2] View Cart\n";
        cout << "[3] Logout\n";
        cout << "[4] Exit\n";
        select_option();
        clear_screen() ;
        if (option == 1)
        {
            browse_products();
        }
        else if (option == 2)
        {
            view_cart();
        }
        else if (option == 3)
        {
            return;
        }
        else if (option == 4)
        {
            exit(0);
        }
        else
        {
            wrong_option();
        }
    }
}

// Displays all products with pagination
void view_all_products()
{
    print_line();
    cout << "    All Products\n";
    print_line();
    cout << left << setw(5) << "ID" << left << setw(30) << "Name" << right << setw(8) << "Price\n";
    
    int number_of_products = 0, index = 0;
    vector<int> last_pages;
    string choice;
    
    for (int pr = 0; pr < products.size(); pr++)
    {
        cout << left << setw(5) << products[pr].id << left << setw(30) << products[pr].name << right << setw(8) << products[pr].price << "\n";
        
        if (number_of_products == 0)
        {
            last_pages.push_back(pr);
        }
        number_of_products++;
        
        if (number_of_products == 10)
        {
            print_thin_line();
            number_of_products = 0;
            cout << "[N] Next Page    [P] Previous Page\n";
            cout << "[B] Back \n";
            cout << "or Enter Product ID for details: ";
            cin >> choice;
            
            if (choice == "N")
            {
                clear_screen();
                index++;
                continue;
            }
            else if (choice == "P")
            {
                clear_screen();
                if (index == 0)
                {
                    pr = --last_pages[index];
                }
                else
                {
                    pr = --last_pages[--index];
                }
            }
            else if (choice == "B")
            {
                clear_screen();
                return;
            }
            else if (choice[0] >= '0' && choice[0] <= '9')
            {
                show_a_details_of_product(choice);
            }
            else
            {
                wrong_option();
                break;
            }
        }
    }
}

// Adds a new product to the system
void add_product()
{
    print_line();
    cout << "    Add New Product\n";
    print_line();
    cout << "Enter Name of Product: ";
    cin.ignore();
    getline(cin, name_of_product);
    cout << "Enter Price of Product: ";
    cin >> price_of_product;
    cout << "Enter Quantity of Product: ";
    cin >> quantity_of_product;
    cout << "Enter Description of Product: ";
    cin.ignore();
    getline(cin, description_of_product);
    
    id_of_product = to_string(products.size());
    category_of_product = "New";
    
    ofstream add("products.txt", ios::app);
    add << id_of_product << "," << name_of_product << "," << price_of_product;
    add << "," << quantity_of_product << "," << category_of_product << "," << description_of_product;
    push_to_products();
    add.close();
    
    cout << "Product added successfully!\n";
    to_next_step();
}

// Seller menu interface
void seller_menu()
{
    while (true)
    {
        print_line();
        cout << "    Seller Menu\n";
        print_line();
        cout << "[1] Add Product\n";
        cout << "[2] View All Products\n";
        cout << "[3] Logout\n";
        cout << "[4] Exit\n";
        print_thin_line();
        select_option();
        clear_screen() ;
        if (option == 1)
        {
            add_product();
        }
        else if (option == 2)
        {
            view_all_products();
        }
        else if (option == 3)
        {
            return;
        }
        else if (option == 4)
        {
            exit(0);
        }
        else
        {
            wrong_option();
        }
    }
}

// Handles user login process
void login_user()
{
    print_line();
    cout << "         Login         \n";
    print_line();
    bool ok = false;
    
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password_of_user;
    clear_screen() ;
    int size = users.size();
    for (int i = 1; i < size; i++)
    {
        if (users[i].username == username && users[i].password == password_of_user)
        {
            id_of_user = users[i].id;
            ok = true;
            break;
        }
    }
    
    if (ok)
    {
        int i = stoi(id_of_user);
        cout << "Welcome " << username << endl;
        
        if (users[i].role == "Customer")
        {
            customer_menu();
        }
        else
        {
            seller_menu();
        }
    }
    else
    {
        cout << "Invalid username or password!\n";
    }
}

// Adds a new user to the system
void add_new_user()
{
    ofstream user("users.txt", ios::app);
    id_of_user = to_string(users.size());
    user << id_of_user;
    user << ",";
    user << username;
    user << ",";
    user << password_of_user;
    user << ",";
    user << role_of_user;
    user << "\n";
    
    push_to_users();
    user.close();
    
    cout << "Account created successfully as " << role_of_user << "!\n";
    to_next_step();
    
    if (role_of_user == "Customer")
    {
        customer_menu();
    }
    else
    {
        seller_menu();
    }
}

// Handles user registration process
void register_user()
{
    string confirm_password;
    print_line();
    cout << "         Register         \n";
    print_line();
    
    cout << "Choose a username: ";
    cin >> username;
    cout << "Choose a password: ";
    cin >> password_of_user;
    cout << "Confirm password: ";
    cin >> confirm_password;
    clear_screen() ;
    if (confirm_password != password_of_user)
    {
        cout << "Passwords don't match, try again.\n";
    }
    else
    {
        cout << "Select your role:\n";
        cout << "[1] Customer\n";
        cout << "[2] Seller\n";
        print_thin_line();
        select_option();
        clear_screen() ;
        if (option == 1)
        {
            role_of_user = "Customer";
        }
        else if (option == 2)
        {
            role_of_user = "Seller";
        }
        else
        {
            wrong_option();
            return;
        }
        
        add_new_user();
    }
}

// Main menu interface
void main_menu()
{
    while (true)
    {
        cout << "[1] Login\n";
        cout << "[2] Register\n";
        cout << "[3] Exit\n";
        print_thin_line();
        select_option();
        clear_screen() ;
        if (option == 1)
        {
            login_user();
        }
        else if (option == 2)
        {
            register_user();
        }
        else if (option == 3)
        {
            return;
        }
        else
        {
            wrong_option();
        }
    }
}
// main function 
int main()
{
    // Initialize data by loading from files
    loading_users();
    loading_cart();
    loading_products();
    
    // Show welcome screen and start main menu
    show_welcome_screen();
    main_menu();
    
    return 0;
}
