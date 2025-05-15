#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Function to clear the console
void clear_console() {
    system("clear"); // Use "cls" for Windows
}

// QuoteModel: Handles the data (quotes)
class QuoteModel {
public:
    QuoteModel() {
        quotes = {
            "The early bird catches the worm.",
            "Actions speak louder than words.",
            "A picture is worth a thousand words."
        };
    }

    // Get a quote by index
    std::string get_quote(int n) const {
        if (n < 0 || n >= quotes.size()) {
            throw std::out_of_range("Index out of range. Please provide a valid index.");
        }
        return quotes[n];
    }

    // Add a new quote
    void add_quote(const std::string& newQuote) {
        quotes.push_back(newQuote);
    }

    // Update an existing quote
    void update_quote(int index, const std::string& updatedQuote) {
        if (index < 0 || index >= quotes.size()) {
            throw std::out_of_range("Invalid index. Unable to update quote.");
        }
        quotes[index] = updatedQuote;
    }

    // Delete a quote
    void delete_quote(int index) {
        if (index < 0 || index >= quotes.size()) {
            throw std::out_of_range("Invalid index. Unable to delete quote.");
        }
        quotes.erase(quotes.begin() + index);
    }

    // Get all quotes
    const std::vector<std::string>& get_all_quotes() const {
        return quotes;
    }

private:
    std::vector<std::string> quotes;
};

// QuoteTerminalView: Handles user interaction
class QuoteTerminalView {
public:
    // Display a single quote
    void display_quote(const std::string& quote) {
        std::cout << "Quote: " << quote << std::endl;
    }

    // Display all quotes
    void display_all_quotes(const std::vector<std::string>& quotes) {
        std::cout << "Quotes List:" << std::endl;
        for (size_t i = 0; i < quotes.size(); ++i) {
            std::cout << i << ": " << quotes[i] << std::endl;
        }
    }

    // Display an error message
    void display_error(const std::string& error) {
        std::cerr << "Error: " << error << std::endl;
    }

    // Get user input
    std::string get_user_input(const std::string& prompt) {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin, input);
        return input;
    }
};

// QuoteTerminalController: Connects the Model and View
class QuoteTerminalController {
public:
    QuoteTerminalController(QuoteModel& model, QuoteTerminalView& view)
        : model(model), view(view) {}

    void run() {
        while (true) {
            clear_console(); // Clear the console before displaying the menu
            view.display_all_quotes(model.get_all_quotes());
            std::string command = view.get_user_input("\nEnter a command (view, add, update, delete, exit): ");

            if (command == "view") {
                handle_view();
            } else if (command == "add") {
                handle_add();
            } else if (command == "update") {
                handle_update();
            } else if (command == "delete") {
                handle_delete();
            } else if (command == "exit") {
                break;
            } else {
                view.display_error("Invalid command. Please try again.");
            }
        }
    }

private:
    QuoteModel& model;
    QuoteTerminalView& view;

    void handle_view() {
        clear_console(); // Clear the console before handling the view
        try {
            int index = std::stoi(view.get_user_input("Enter the index of the quote to view: "));
            view.display_quote(model.get_quote(index));
        } catch (const std::exception& e) {
            view.display_error(e.what());
        }
        wait_for_user();
    }

    void handle_add() {
        clear_console(); // Clear the console before handling add
        std::string newQuote = view.get_user_input("Enter the new quote: ");
        model.add_quote(newQuote);
        std::cout << "Quote added successfully!" << std::endl;
        wait_for_user();
    }

    void handle_update() {
        clear_console(); // Clear the console before handling update
        try {
            int index = std::stoi(view.get_user_input("Enter the index of the quote to update: "));
            std::string updatedQuote = view.get_user_input("Enter the updated quote: ");
            model.update_quote(index, updatedQuote);
            std::cout << "Quote updated successfully!" << std::endl;
        } catch (const std::exception& e) {
            view.display_error(e.what());
        }
        wait_for_user();
    }

    void handle_delete() {
        clear_console(); // Clear the console before handling delete
        try {
            int index = std::stoi(view.get_user_input("Enter the index of the quote to delete: "));
            model.delete_quote(index);
            std::cout << "Quote deleted successfully!" << std::endl;
        } catch (const std::exception& e) {
            view.display_error(e.what());
        }
        wait_for_user();
    }

    void wait_for_user() {
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};

// Main function
int main() {
    QuoteModel model;
    QuoteTerminalView view;
    QuoteTerminalController controller(model, view);

    controller.run();
    return 0;
}