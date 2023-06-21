#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Contact
{
	std::string name;
	std::string surname;
	std::string phoneNumber;
	std::string email;
	std::string address;
};
std::vector<Contact> contacts;

//Function For Phone Number.				
bool PhoneNumber(const std::string& phoneNumber)
{
	std::string numberPrefix = "+374";
	if(phoneNumber.substr(0,numberPrefix.length()) != numberPrefix || phoneNumber.length() != (numberPrefix.length() + 8) || !(std::all_of(phoneNumber.begin() + 
					numberPrefix.length(),phoneNumber.end(),::isdigit)))
	{
		std::cout << "Invalid Phone Number!" << std::endl;
		std::cout << "Please, Enter valid phone number  starting with" << numberPrefix << std::endl;
		return false;
	}
	return true;
}

// Function For Email.
bool email(const std::string& email)
{
	std::vector<std::string> domain = {"@mail.ru", "@gmail.com", "@bk.ru", "@yandex.ru", "@inbox.ru", "@list.ru","@yahoo.com","@outlook.com"};
	size_t symbol = email.find('@');
	if (symbol == std::string::npos)
	{
		std::cout << "Invalid el-address" << std::endl;
		return false;
	}
	std::string el_domain = email.substr(symbol);
	if (std::find(domain.begin(),domain.end(), el_domain) == domain.end())
	{	
		std::cout << "Invalid el-address" << std::endl;
		std::cout << "Please,Enter valid eladdress with one of domains" << std::endl;
		return false;
	}
	return true;
}
//Function For Saving

void saveInFile() {
	std::ofstream outputFile("contact.txt");
	if (outputFile.is_open()) {
		for (const auto& contact : contacts) {
			outputFile << contact.name << "," << contact.surname << "," << contact.phoneNumber << "," << contact.email << ","  << contact.address << std::endl;
		}
		outputFile.close();
		std::cout << "Contacts saved to file." << std::endl;
	} else {
		std::cout << "Unable to save contacts to file." << std::endl;
	}
}

// Function For Loading in File
void loadingInFile ()
{
	std::ifstream inputFile("contact.txt");
	if (inputFile.is_open())
	{
		contacts.clear();
		std::string line;
		while (std::getline(inputFile, line))
		{
			Contact m_contact;
			size_t pos = 0;
			std::string token;
			std::string delimetr = ",";
			int count = 0;
			while ((pos = line.find(delimetr) ) != std::string::npos)
			{
				token = line.substr(0, pos);
				line.erase(0,pos + delimetr.length());
				switch (count)
				{
					case 0:
						m_contact.name = token;
						break;
					case 1:
						m_contact.surname = token;
						break;
					case 2:
						m_contact.phoneNumber = token;
						break;
					case 3:
						m_contact.email = token;
						break;
				}
				++count;
			}
			m_contact.address = line;	
			contacts.push_back(m_contact);
		}
		inputFile.close();
		std::cout << "Contacts Load in File" << std::endl;	
	}
	else
	{
		std::cout << "Unable to load contacts from file." << std::endl;
	}
}

//Function For Add contact
void addContact()
{
	Contact contact;
	std::cout << "PLease,Enter Name" << std::endl;
	std::cin >> contact.name;
	std::cout << "Please,Enter SurName" << std::endl;
	std::cin >> contact.surname;
	while (true)
	{
		std::cout << "Please,enter Phone Number" << std::endl;
		std::cin >> contact.phoneNumber;
		if (PhoneNumber(contact.phoneNumber))
		{
			break;
		}
	}
	while (true)
	{
		std::cout << "Please,Enter email" << std::endl;
		std::cin >> contact.email;
		if (email(contact.email))
		{
			break;
		}
	}
	std::cout << "Please,Enter Address" << std::endl;
	std::cin.ignore();
	std::getline(std::cin,contact.address);
	contacts.push_back(contact);
	std::cout << "contact Address is OK" << std::endl;
	saveInFile();
}

//Function For Display

void displayContact ()
{
	std::cout << "Contacts:" << std::endl;
	for (const auto&  contact : contacts)
	{
		std::cout << "Name: " << contact.name << std::endl;
        std::cout << "Surname: " << contact.surname << std::endl;
        std::cout << "Phone Number: " << contact.phoneNumber << std::endl;
        std::cout << "Email: " << contact.email << std::endl;
        std::cout << "Address: " << contact.address << std::endl;
        std::cout << std::endl;
	}
}

// Function For Remove contact
void removeContact()
{
	if (contacts.empty())
	{
		std::cout << "No Contact for remove" << std::endl;
		return;
	}
	std::string searchName;
	std::cout << "Please,Enter Name wich you want remove" << std::endl;
	std::cin >> searchName;
	 auto iter = std::find_if(contacts.begin(), contacts.end(), [&] (const Contact& contact) { return contact.name == searchName; });
	if (iter != contacts.end())
	{
		Contact& contact = *iter;
        std::cout << "Enter new name: ";
        std::cin >> contact.name;
        std::cout << "Enter new surname: ";
        std::cin >> contact.surname;
	while (true)
	{
		std::cout << "Enter New Phone Number" << std::endl;
		std::cin >> contact.phoneNumber;
		if (PhoneNumber(contact.phoneNumber))
		{
			break;
		}
	}
	while (true) 
	{
            std::cout << "Enter new email: ";
            std::cin >> contact.email;
            if (email(contact.email)) {
                break;

    }
}
	std::cout << "Enter New Address" << std::endl;
	std::cin.ignore(); 
        std::getline(std::cin, contact.address);
        std::cout << "Contact updated successfully." << std::endl;
        saveInFile();
    } 
	else 
	{
        std::cout << "Contact not found." << std::endl;
    	}
}

//Function For Updateing
void updateContact() 
{
    if (contacts.empty()) 
    {
        std::cout << "No contacts to update." << std::endl;
        return;
    }
    std::string searchName;
    std::cout << "Enter the name of the contact to update: ";
    std::cin >> searchName;
    auto iter = std::find_if(contacts.begin(), contacts.end(), [&](const Contact& contact) { return contact.name == searchName; });
    if (iter != contacts.end()) {
        Contact& contact = *iter;
        std::cout << "Enter new name: ";
        std::cin >> contact.name;
        std::cout << "Enter new surname: ";
        std::cin >> contact.surname;
        while (true) {
            std::cout << "Enter new phone number: " << std::endl;
            std::cin >> contact.phoneNumber;
            if (PhoneNumber(contact.phoneNumber)) {
                break;
            }
        }
        while (true) {
            std::cout << "Enter new email: " << std::endl;
            std::cin >> contact.email;
            if (email(contact.email)) 
	    {
                break;
            }
        }
        std::cout << "Enter new address: " << std::endl;
        std::cin.ignore(); 
        std::getline(std::cin, contact.address);
        
        std::cout << "Contact updated successfully." << std::endl;
        saveInFile();
    } else {
        std::cout << "Contact not found." << std::endl;
    }
}

//Function For Search
void searchContact() 
{
    if (contacts.empty()) 
    {
        std::cout << "No contacts to search." << std::endl;
        return;
    }
    
    std::string searchString;
    std::cout << "Enter the string to search: ";
    std::cin >> searchString;
    std::vector<Contact> searchResults;
    for (const auto& contact : contacts) 
    {
        if (contact.name.find(searchString) != std::string::npos || contact.surname.find(searchString) != std::string::npos ||
		       	contact.phoneNumber.find(searchString) != std::string::npos || contact.email.find(searchString) != std::string::npos
		       	||  contact.address.find(searchString) != std::string::npos) {
                        searchResults.push_back(contact);
        }
    }
    
    if (searchResults.empty()) 
    {
        std::cout << "No contacts found matching the search criteria." << std::endl;
    } 
    else 
    {
        std::cout << "Search Results:" << std::endl;
        for (const auto& contact : searchResults)
       	{
            std::cout << "Name: " << contact.name << std::endl;
            std::cout << "Surname: " << contact.surname << std::endl;
            std::cout << "Phone Number: " << contact.phoneNumber << std::endl;
            std::cout << "Email: " << contact.email << std::endl;
            std::cout << "Address: " << contact.address << std::endl;
            std::cout << std::endl;
        }
    }
}

int main()
{
    loadingInFile();

    while (true) 
    {
        std::cout << "Address Book Menu:" << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. Display Contacts" << std::endl;
        std::cout << "3. Remove Contact" << std::endl;
        std::cout << "4. Update Contact" << std::endl;
        std::cout << "5. Search Contacts" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your WhatYouWant: ";
        int WhatYouWant;
        std::cin >> WhatYouWant;

        switch (WhatYouWant) 
	{
            case 1:
                addContact();
                break;
            case 2:
                displayContact();
                break;
            case 3:
                removeContact();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                searchContact();
                break;
            case 6:
                saveInFile();
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;
    }
    return 0;
}
