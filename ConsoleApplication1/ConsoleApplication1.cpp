#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <chrono> 
using namespace std::chrono; 
using std::cout;
using std::cin;

/*
The program provides a trading terminal with the functionality of adding, changing and deleting orders to buy and sell.
The Glass class manages orders, and CheckOperations checks the correctness of the entered data.
The program supports saving and loading data to a file, as well as measuring the execution time of operations.
*/


class CheckOperations;
class Glass {
private:

    std::string price;
    std::string count;
    std::string type;

    int sub;

    std::vector<std::vector<std::string>> data;
    std::vector<std::vector<std::string>> dataForBuy;
    std::vector<std::vector<std::string>> dataForSell;

    void Gswap(std::vector<std::string>& data1, std::vector<std::string>& data2) {
        std::vector<std::string> temp = data1;
        data1 = data2;
        data2 = temp;
    }

    void minPrice(std::vector<std::vector<std::string>>& data) {      
        for (size_t i = 0; i < dataForBuy.size(); ++i) {
            int minPrice = stoi(dataForBuy[i][0]);
            for (size_t j = i + 1; j < dataForBuy.size(); ++j) {
                int newMinPrice = stoi(dataForBuy[j][0]);
                if (newMinPrice < minPrice) {
                    minPrice = newMinPrice;
                    Gswap(dataForBuy[i], dataForBuy[j]);
                }
            }
        }
    }

    void maxPrice(std::vector<std::vector<std::string>>& data) {
        for (size_t i = 0; i < dataForSell.size(); ++i) {
            int maxPrice = stoi(dataForSell[i][0]);
            for (size_t j = i + 1; j < dataForSell.size(); ++j) {
                int newMaxPrice = stoi(dataForSell[j][0]);
                if (newMaxPrice > maxPrice) {
                    maxPrice = newMaxPrice;
                    Gswap(dataForSell[i], dataForSell[j]);
                }
            }
        }
    }
    
public:
   
    Glass(const std::string& type, const std::string& price, const std::string& count) : price(price), count(count), type(type), sub(1) {}
    
    void AddApplication(const std::string& price, const std::string& count, const std::string& type) { 
        std::vector<std::string> temp;
        temp.push_back(price);
        temp.push_back(count);
        temp.push_back(type);
        data.push_back(temp);

        if (data[sub - 1][2] == "buy") { dataForBuy.push_back(temp); }
        if (data[sub - 1][2] == "sell") { dataForSell.push_back(temp); }
        
        temp.clear();
        sub++;
    }

    const std::vector<std::vector<std::string>>& getData() const {
        return data;
    }

    void clearData() {
        if (!data.empty()) { data.clear(); }
        else if (!dataForBuy.empty()) { dataForBuy.clear(); }
        else if (!dataForSell.empty()) { dataForSell.clear(); }
        
        sub = 1;
    }

    template <typename Func>
    void MeasureTimeForMethod(const std::string& methodName, Func&& method) {  
        auto start = high_resolution_clock::now();
        method();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        cout << "Time taken by " << methodName << ": " << duration.count() << " milliseconds" << std::endl;

    }

    void ChangeApplication(int index, const std::string& newPrice, const std::string& newCount, const std::string & newType) {    
        MeasureTimeForMethod("ChangeApplication", [=] {   
            if (!data.empty() && index >= 0 && index <= data.size() - 1) {
                data[index][0] = newPrice;
                data[index][1] = newCount;
                data[index][2] = newType;
            }
            else {
                cout << "Application not found." << std::endl;
            }
        });
    }
    void DeleteApplication(int index) {
        MeasureTimeForMethod("showForSell", [=] {
            if (!data.empty() && index >= 0 && index <= data.size() - 1) {
                data.erase(data.begin() + index);
            }
            else {
                cout << "Application not found." << std::endl;
            }
        });
    }

    void showTop10forBuy() {   
        MeasureTimeForMethod("showForSell", [=] {
            minPrice(dataForBuy);
            if (dataForBuy.size() >= 10) {
                cout << "Best for Buy" << std::endl;
                for (size_t i = 0; i < 10; ++i) {
                    cout << "- ";
                    for (size_t j = 0; j < dataForBuy[i].size(); ++j) {
                        if (j == dataForBuy[i].size() - 1) {
                            cout << dataForBuy[i][j] << '\n';
                            break;
                        }
                        cout << dataForBuy[i][j] << " : ";
                    }
                }
            }
            else {
                cout << "There are too few applications." << '\n';
                cout << "Currently the number of applications: " << dataForBuy.size();
            }
        });
    }

    void showTop10forSell(){
        MeasureTimeForMethod("showForSell", [=] {
            maxPrice(dataForSell);
            if (dataForSell.size() >= 10) {
                cout << "Best for Sell" << std::endl;
                for (size_t i = 0; i < 10; ++i) {
                    cout << "- ";
                    for (size_t j = 0; j < dataForSell[i].size(); ++j) {
                        if (j == dataForSell[i].size() - 1) {
                            cout << dataForSell[i][j] << '\n';
                            break;
                        }
                        cout << dataForSell[i][j] << " : ";
                    }
                }
            }
            else {
                cout << "There are too few applications." << '\n';
                cout << "Currently the number of applications: " << dataForSell.size();
            }
        });
    }

    void ShowAllApplications() {
        MeasureTimeForMethod("showForSell", [=] {
            if (!data.empty()) {
                for (size_t i = 0; i < data.size(); ++i) {
                    cout << "- ";
                    for (size_t j = 0; j < data[i].size(); ++j) {
                        if (j == data[i].size() - 1) {
                            cout << data[i][j] << '\n';
                            break;
                        }
                        cout << data[i][j] << " : ";
                    }
                }
            }
            else {
                cout << "There are currently no applications on the exchange" << "\n";
            }
        });
    }

    void showForBuy() {
        MeasureTimeForMethod("showForSell", [=] {
            if (!dataForBuy.empty()) {
                for (size_t i = 0; i < dataForBuy.size(); ++i) {
                    cout << "- ";
                    for (size_t j = 0; j < dataForBuy[i].size(); ++j) {
                        if (j == dataForBuy[i].size() - 1) {
                            cout << dataForBuy[i][j] << '\n';
                            break;
                        }
                        cout << dataForBuy[i][j] << " : ";
                    }
                }
            }
            else {
                cout << "There are no purchase applications at this time." << "\n";
            }
        });
    }

    void showForSell() {
        MeasureTimeForMethod("showForSell", [=] {
            if (!dataForSell.empty()) {
                for (size_t i = 0; i < dataForSell.size(); ++i) {
                    cout << "- ";
                    for (size_t j = 0; j < dataForSell[i].size(); ++j) {
                        if (j == dataForSell[i].size() - 1) {
                            cout << dataForSell[i][j] << '\n';
                            break;
                        }
                        cout << dataForSell[i][j] << " : ";
                    }
                }
            }
            else {
                cout << "At the moment there are no offers for sale on the exchange.." << "\n";
            }
        });
    }

};

class CheckOperations {
public:
    bool IsRightType(const std::string& type) {
        return (type == "sell" || type == "buy");
    }

    bool IsRightPrice(const std::string& price) {
        try {
            int len = 0;
            for (const auto& ch : price) {
                if (std::stoi(std::string(1, ch))) {
                    ++len;
                }
            }
            return len == price.length();
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid input for price. " << e.what() << std::endl;
            return false;
        }
    }

    bool IsRightCount(const std::string& count) {
        try {
            int len = 0;
            for (const auto& ch : count) {
                if (std::stoi(std::string(1, ch))) {
                    ++len;
                }
            }
            return len == count.length();
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid input for count. " << e.what() << std::endl;
            return false;
        }
    }
};
void SaveToFile(const Glass& glass, const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& application : glass.getData()) {
            file << application[0] << " " << application[1] << " " << application[2] << "\n";
        }

        file.close();
        std::cout << "Data saved to " << filename << std::endl;
    }
    else {
        std::cerr << "\n" << "Unable to open file for writing: " << filename << std::endl;
    }
}
void LoadFromFile(Glass& glass, const std::string& filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        glass.clearData();

        std::string price, count, type;
        while (file >> price >> count >> type) {
            glass.AddApplication(price, count, type);
        }
        std::cout << "\n" << "Data loaded from " << filename << std::endl;
        file.close();
    }
    else {
        std::cerr << "\n" << "Unable to open file for reading: " << filename << std::endl;
    }
}
int main() {

    cout << "An order is a price, volume(quantity) and type(Buy or Sell)." << std::endl;
    cout << "There are 4 commands:" << std::endl;
    cout << "1. Add a request" << std::endl;
    cout << "2. Change the application" << std::endl;
    cout << "3. Delete the application" << std::endl;
    cout << "4. Display the top 10 applications for buy." << std::endl;
    cout << "5. Display the top 10 applications for sell." << std::endl;
    cout << "6. Display all applications." << std::endl;
    cout << "7. Display the applications for buy." << std::endl;
    cout << "8. Display the applications for sell." << std::endl;
    cout << "9. Delete all applications" << std::endl;
    cout << "10. Exit the program" << std::endl;
    
    Glass g("", "", "");
    CheckOperations Check;
    LoadFromFile(g, "data.txt");
    
    cout << "\n" << "Select operation: ";
    
    while (true) {
        
        int op;
        cin >> op;
        std::string price, count, type;
        int IndexForChange;
        int IndexForDelete;        
        std::string newPrice, newCount, newType;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            if (op <= 0 || op > 10) {
                cout << "Wrong operation! Try again." << '\n';
                cout << "Enter operation: ";
            }
            if (op == 1) {
                std::string price, count, type;
                
                cout << "Enter price: ";
                getline(cin, price);
                cout << "Enter count: ";
                getline(cin, count);
                cout << "Enter type: ";
                getline(cin, type);
               
                if (Check.IsRightCount(count) && Check.IsRightPrice(price) && Check.IsRightType(type)) {
                    g.AddApplication(price, count, type);
                    cout << '\n' << "Enter operation: ";
                }
                else {
                    cout << "The application was completed incorrectly. Try again." << "\n" << "Enter: ";
                }
                
            }
            else if(op == 2) {
                
                cout << "Enter the index(starts from 0) of Application which you wanna change: ";
                cin >> IndexForChange;
                cout << std::endl << "Enter new price: ";
                cin >> newPrice;
                cout << std::endl << "Enter new cout: ";
                cin >> newCount;
                cout << std::endl << "Enter new type(sell or buy): ";
                cin >> newType;
                
                if (Check.IsRightCount(newCount) && Check.IsRightPrice(newPrice) && Check.IsRightType(newType)) {
                    g.ChangeApplication(IndexForChange, newPrice, newCount, newType);
                    cout << '\n' << "Enter operation: ";
                }
                else {
                    cout << "The application was changed incorrectly. Try again." << "\n" << "Enter operation: ";
                }

            }
            else if (op == 3) {
                
                cout << "Enter the index(starts from 0) of Application which you wanna delete: ";
                cin >> IndexForDelete;
                g.DeleteApplication(IndexForDelete);
                cout << '\n' << "Enter operation: ";

            }
            try {
                if (op == 4) {
                    g.showTop10forBuy();
                    cout << '\n' << "Enter operation: ";
                }
                else if (op == 5) {
                    g.showTop10forSell();
                    cout << '\n' << "Enter operation: ";
                }
                else if (op == 6) {
                    g.ShowAllApplications();
                    cout << '\n' << "Enter operation: ";
                }
                else if (op == 7) {
                    g.showForBuy();
                    cout << '\n' << "Enter operation: ";
                }
                else if (op == 8) {
                    g.showForSell();
                    cout << '\n' << "Enter operation: ";
                }
                else if (op == 9) {
                    g.clearData();
                    cout << "All applications have been successfully deleted" << '\n';
                    cout << '\n' << "Enter operation: ";
                }
                else if (op == 10) {
                    
                    std::string Exit;
                    cout << "Are you sure you want to leave the program? (Yes/No )" << std::endl;
                    cout << "Write your choice: ";
                    cin >> Exit;
                    
                    if (Exit == "Yes") {
                        SaveToFile(g, "data.txt");
                        cout << "Goodbuy!" << std::endl;
                        break;
                    }
                    else if (Exit == "No") {
                        cout << '\n' << "Nice! Enter operation: ";
                    }
                }
            }
            catch (const std::exception& e) {
                std::cerr << "Exception caught:" << e.what() << std::endl;
            }

        }
        catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
        }
    }
    return 0;
}
