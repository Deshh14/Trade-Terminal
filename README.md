# Trade-Terminal
This is a simple trading terminal console application that allows users to manage market orders. Users can perform various operations, including adding, modifying, and deleting orders. The application also provides functionality to display top buy and sell orders, all orders, and specific orders for buying and selling. Additionally, it supports measuring the execution time of different operations.

Table of Contents
-	Features
-	Getting Started
-	Prerequisites
-  Installation
-	Usage
-	Commands
-	Data Persistence
-	Contributing
-	License		

Features
- Add, modify, and delete market orders.
- Display top buy and sell orders.
- Show all market orders.
- View specific orders for buying and selling.
- easure execution time for various operations.

Getting Started:

Prerequisites:
- C++ compiler
- Git (optional)
  
Installation:
1. Clone the repository:
      git clone https://github.com/your-username/trading-terminal.git

      Alternatively, download the ZIP file and extract it.

2. Compile the code using your C++ compiler:

      g++ -o trading_terminal main.cpp

      Replace g++ with your C++ compiler command if needed.
3. Usage
   1. Run the compiled executable: ./trading_terminal
   2. Follow the on-screen prompts to perform various operations.

      Commands:
  
          1: Add a new market order
    
          2: Modify an existing market order
    
          3: Delete a market order
    
          4: Display top 10 buy orders
    
          5: Display top 10 sell orders
    
          6: Show all market orders
    
          7: Display buy orders
    
          8: Display sell orders
    
          9: Delete all orders
    
          10: Exit the program

Data Persistence:

    The application supports data persistence by saving market orders to a file (data.txt). The data is automatically loaded when the program starts.
Contributing:
    
    Contributions are welcome! Feel free to open issues or pull requests.

License:
    
    This project is licensed under the MIT License.
