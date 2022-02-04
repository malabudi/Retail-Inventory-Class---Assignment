#include <iostream>
#include <limits>

// Classes
class RetailItem
{
    private:
        int itemID;
        static int newItemID;
        std::string description;
        int unitsOnHand;
        double price;
        int reorderQuantity;

    public:
        // Default Constructor
        RetailItem();

        // Non-Default Constructor
        RetailItem(std::string description, int unitsOnHand, double price, int reorderQuantity);

        // Mutators
        void setDescription(std::string description)    { this->description = description; }
        void setUnitsOnHand(int unitsOnHand)            { this->unitsOnHand = unitsOnHand; }
        void setPrice(double price)                     { this->price = price; }
        void setReorderQuantity(int reorderQuantity)    { this->reorderQuantity = reorderQuantity; }

        // Accessors
        int getItemID()                 { return itemID; }
        std::string getDescription()    { return description; }
        int getUnitsOnHand()            { return unitsOnHand; }
        double getPrice()               { return price; }
        int getReorderQuantity()        { return reorderQuantity; }
};

// Implementations
int RetailItem::newItemID = 1;

RetailItem::RetailItem()
    {
        this->itemID = newItemID++;
        description = "";
        unitsOnHand = 0;
        price = 0.00;
        reorderQuantity = 0;
    }

RetailItem::RetailItem(std::string description, int unitsOnHand, double price, int reorderQuantity)
    {
        this->itemID = newItemID++;
        this->description = description;
        this->unitsOnHand = unitsOnHand;
        this->price = price;
        this->reorderQuantity = reorderQuantity;
    }


// Function Prototypes
int displayMenu();
bool isNotValidMenuChoice(int choice);
void addItem(RetailItem inventoryItems[], int& currentItems, const int INVENTORY_SIZE);
void validateItemEntry(int& data, std::string entry);
void validateItemEntry(double& data, std::string entry);
void displayAllItems(RetailItem inventoryItems[], int currentItems);
void checkItemInInventory(RetailItem inventoryItems[], int currentItems);
void displayItemsToReorder(RetailItem inventoryItems[], int currentItems);
void updateItem(RetailItem inventoryItems[], int currentItems);


int main()
{
    // declare variables & objects
    const int INVENTORY_SIZE = 20;
    int menuChoice, currentItem = 0;
    RetailItem inventoryItems[INVENTORY_SIZE];

    std::cout << "Welcome to the Retail Inventory Management Program" << std::endl;

    while(true)
    {
        menuChoice = displayMenu();

        switch(menuChoice)
        {
            case 1:
                addItem(inventoryItems, currentItem, INVENTORY_SIZE);
                break;
            case 2:
                displayAllItems(inventoryItems, currentItem);
                break;
            case 3:
                checkItemInInventory(inventoryItems, currentItem);
                break;
            case 4:
                displayItemsToReorder(inventoryItems, currentItem);
                break;
            case 5:
                updateItem(inventoryItems, currentItem);
                break;
            case 6:
                std::cout << "\nThank you, closing  the retail inventory management program..." << std::endl;
                return 0;
        }
    }

    return 0;
}


// User defined functions
int displayMenu()
{
    int choice;

    std::cout << "\nPlease select an item from the menu (1-5):" << std::endl;
    std::cout << "1 - Add an item to inventory" << std::endl;
    std::cout << "2 - Display all items in inventory" << std::endl;
    std::cout << "3 - Check to see if an item is in inventory" << std::endl;
    std::cout << "4 - Display only those items that need to be re-ordered" << std::endl;
    std::cout << "5 - Update an item in inventory" << std::endl;
    std::cout << "6 - Close the program" << std::endl;
    std::cin >> choice;

    while(isNotValidMenuChoice(choice))
    {
        std::cout << "Your input is invalid, please make sure you have entered 1-5." << std::endl;

        std::cout << "\nPlease select an item from the menu (1-5):" << std::endl;
        std::cout << "1 - Add an item to inventory" << std::endl;
        std::cout << "2 - Display all items in inventory" << std::endl;
        std::cout << "3 - Check to see if an item is in inventory" << std::endl;
        std::cout << "4 - Display only those items that need to be re-ordered" << std::endl;
        std::cout << "5 - Update an item in inventory" << std::endl;
        std::cout << "6 - Close the program" << std::endl;
        std::cin >> choice;
    }

    return choice;
}


bool isNotValidMenuChoice(int choice)
{
    if (choice <= 0 || choice >= 7 || std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return true;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return false;
}


void addItem(RetailItem inventoryItems[], int& currentItems, const int INVENTORY_SIZE)
{
    if (currentItems == INVENTORY_SIZE)
    {
        std::cout << "Inventory full! Unable to add any more items." << std::endl;
        return;
    }

    // variables to contain the input data
    std::string description;
    int unitsOnHand;
    double price;
    int reorderQuantity;

    // Ask for input and update the local variables first
    std::cout << "\nPlease enter the description of the item: ";
    std::getline(std::cin, description);
    std::cout << "\nPlease enter the current available units of the item: ";
    std::cin >> unitsOnHand;

    validateItemEntry(unitsOnHand, "units on hand");

    std::cout << "\nPlease enter the current price of the item: $";
    std::cin >> price;

    validateItemEntry(price, "item price");

    std::cout << "\nPlease enter the reorder quantity of the item: ";
    std::cin >> reorderQuantity;

    validateItemEntry(reorderQuantity, "reorder quantity");

    // Now mutate the inventoryItem object
    inventoryItems[currentItems].setDescription(description);
    inventoryItems[currentItems].setUnitsOnHand(unitsOnHand);
    inventoryItems[currentItems].setPrice(price);
    inventoryItems[currentItems].setReorderQuantity(reorderQuantity);

    currentItems++;
}


void validateItemEntry(int& data, std::string entry)
{
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cerr << "\nInvalid input for " << entry << std::endl;
        std::cout << "Please enter your input again: ";
        std::cin >> data;
    }
}


void validateItemEntry(double& data, std::string entry)
{
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cerr << "\nInvalid input for " << entry << std::endl;
        std::cout << "Please enter your input again: ";
        std::cin >> data;
    }
}


void displayAllItems(RetailItem inventoryItems[], int currentItems)
{
    std::cout << "\n-------------------------------------------\n" << std::endl;

    int i;
    for (i = 0; i < currentItems; i++)
    {
        std::cout << "Item ID: " << inventoryItems[i].getItemID() << std::endl;
        std::cout << "Description: " << inventoryItems[i].getDescription() << std::endl;
        std::cout << "Current Units on Hand: " << inventoryItems[i].getUnitsOnHand() << std::endl;
        std::cout << "Price: $" << inventoryItems[i].getPrice() << std::endl;
        std::cout << "Reorder Quantity: " << inventoryItems[i].getReorderQuantity() << std::endl;
        std::cout << "\n-------------------------------------------\n" << std::endl;
    }
}


void checkItemInInventory(RetailItem inventoryItems[], int currentItems)
{
    std::string itemToCheck;

    std::cout << "Please enter the description of the item: ";
    std::getline(std::cin, itemToCheck);

    int i;
    for (i = 0; i < currentItems; i++)
    {
        // use compare method to see if strings are equal
        if (itemToCheck.compare(inventoryItems[i].getDescription()) == 0)
        {
            std::cout << "\n" << itemToCheck << " is currently in the inventory." << std::endl;
            return;
        }
    }

    std::cout << "\nSorry, but " << itemToCheck << " has not been found." << std::endl;
}


void displayItemsToReorder(RetailItem inventoryItems[], int currentItems)
{
    std::cout << "\n-------------------------------------------\n" << std::endl;

    int i;
    for (i = 0; i < currentItems; i++)
    {
        if (inventoryItems[i].getUnitsOnHand() <= inventoryItems[i].getReorderQuantity() && inventoryItems[i].getReorderQuantity() > 0)
        {
            std::cout << "Item ID: " << inventoryItems[i].getItemID() << std::endl;
            std::cout << "Description: " << inventoryItems[i].getDescription() << std::endl;
            std::cout << "Current Units on Hand: " << inventoryItems[i].getUnitsOnHand() << std::endl;
            std::cout << "Price: $" << inventoryItems[i].getPrice() << std::endl;
            std::cout << "Reorder Quantity: " << inventoryItems[i].getReorderQuantity() << std::endl;
            std::cout << "\n-------------------------------------------\n" << std::endl;
        }
    }
}


void updateItem(RetailItem inventoryItems[], int currentItems)
{
    std::string itemToUpdate;
    int newQuantiy, newReorderQuantity;
    double newPrice;

    std::cout << "\nPlease enter the description of the item you would like to update: ";
    std::getline(std::cin, itemToUpdate);

    int i;
    for (i = 0; i < currentItems; i++)
    {
        if (itemToUpdate.compare(inventoryItems[i].getDescription()) == 0)
        {
            // Display item with current values of its class members
            std::cout << "\n-------------------------------------------" << std::endl;
            std::cout << "Current Item ID: " << inventoryItems[i].getItemID() << std::endl;
            std::cout << "Current Description: " << inventoryItems[i].getDescription() << std::endl;
            std::cout << "Current Units on Hand: " << inventoryItems[i].getUnitsOnHand() << std::endl;
            std::cout << "Current Price: $" << inventoryItems[i].getPrice() << std::endl;
            std::cout << "Current Reorder Quantity: " << inventoryItems[i].getReorderQuantity() << std::endl;
            std::cout << "-------------------------------------------\n" << std::endl;

            // Grab the updated values
            std::cout << "Please enter the new current units of the item: ";
            std::cin >> newQuantiy;
            validateItemEntry(newQuantiy, "units on hand");
            std::cout << "Please enter the new price of the item: $";
            std::cin >> newPrice;
            validateItemEntry(newPrice, "item price");
            std::cout << "Please enter the new reorder quantity: ";
            std::cin >> newReorderQuantity;
            validateItemEntry(newReorderQuantity, "reorder quantity");

            inventoryItems[i].setUnitsOnHand(newQuantiy);
            inventoryItems[i].setPrice(newPrice);
            inventoryItems[i].setReorderQuantity(newReorderQuantity);

            return;
        }
    }

}
