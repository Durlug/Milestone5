//Milestone 4
//OnShelf.cpp
//Shaun Richardson
//110392156
//srichardson6@myseneca.ca

#include <string>
#include <iostream>
#include <iomanip>

#include "OnShelf.h"

using namespace std;
namespace ict 
{
	//Constructor (single param)
	OnShelf::OnShelf(char filetag_)
	{
		this->recTag_ = filetag_;
	}

	//Public Member functions
	//ReadWritable methods

	std::fstream& OnShelf::store(std::fstream& file, bool addNewLine)const
	{
		
		file << recTag_ << "," << sku() << "," << name() << "," << price() << "," << taxed() << "," << quantity() << "," << qtyNeeded();
		if (addNewLine)
		{
			file << std::endl;
		}
		return file;

	}

	std::fstream& OnShelf::load(std::fstream& file)
	{
		

		//Temporary Variables Declaration
		char a[MAX_UPC_LEN + 1];
		char b[MAX_NAM_LEN];
		int tax = 0, qty, qtyN;
		double p;

		//Getting Content and Storing them in Appropriate Variables
		file.getline(a, MAX_UPC_LEN + 1, ',');
		file.getline(b, MAX_NAM_LEN, ',');
		file >> p;
		file.ignore(1);
		file >> tax;
		file.ignore(1);
		file >> qty;
		file.ignore(1);
		file >> qtyN;
		file.ignore();

		//Calling Setters
		sku(a);
		name(b);
		price(p);
		if (tax) 
		{
			taxed(true);   //if Tax has a value of 1 
		}
		else 
		{
			taxed(false);  //if Tax has a value of 0
		};
		quantity(qty);
		qtyNeeded(qtyN);
		
		

		return file;
	}


	std::ostream& OnShelf::display(ostream& os, bool linear) const
	{
		if (err_.isClear() == false)
		{
			os << err_.message();
			return os;
		}
		else if (linear)
		{
			os << setfill(' ') << left << setw(MAX_SKU_LEN) << sku() << "|"
			   << setw(20) << name() << "|"
			   << right << setprecision(2) << setw(7) << showpoint << fixed << cost() << '|';
			if (taxed())   //If good is taxed (true)
			{
				os << " t |";
			}
			else
			{
				os << "   |";
			}
			os << setw(4) << quantity() << '|'
				<< setw(4) << qtyNeeded() << '|' << endl;
		}
		else
		{
			os << "Sku: " << sku() << endl;
			os << "Name: " << name() << endl;
			os << "Price: " << price() << endl;
			if (taxed() == true)
			{
				os << "Price after tax: " << (TAX + 1) * price() << endl;
			}
			else
			{
				os << "Price after tax: N/A" << endl;
			}
			
			os << "Quantity On Hand: " << quantity() << endl;
			os << "Quantity Needed: " << qtyNeeded();
		}
		return os;
	}

	istream& OnShelf::conInput(istream& istr)
	{
		//Variable Declaration
		char a[MAX_UPC_LEN + 1];
		char b[256];
		char tax;
		int qty, qtyN;
		double p;

		if (istr.fail() == false) //Checking for failure
		{
			err_.clear();
			cout << "Sku: ";
			istr >> a;
			if (istr.fail() == false)
			{
				sku(a);
			}

			cout << "Name: ";
			istr >> b;
			if (istr.fail() == false)
			{
				name(b);
			}

			cout << "Price: ";
			istr >> p;
			if (istr.fail() == false)
			{
				price(p);
			}
			else
				err_.message("Invalid Price Entry");

			if (err_.isClear())
			{
			
				cout << "Taxed: ";
				istr >> tax;
				if (tax == 'Y' || tax == 'y')  //If user enters Y or y for good being taxed
				{
					istr.clear();
					taxed(true);
				}
				else if (tax == 'N' || tax == 'n')
				{
					istr.clear();
					taxed(false);
	
				}
				else
				{
					err_.message("Only (Y)es or (N)o are acceptable");
					istr.setstate(std::ios::failbit);
				}
			}

				if (err_.isClear())    //Making sure program is Error free (if not skip entry inputting)
			{
				cout << "Quantity On hand: ";
				istr >> qty;
				if (istr.fail() == false)
				{
					quantity(qty);
				}
				else
					err_.message("Invalid Quantity Entry");
			}

			if (err_.isClear())    //Making sure program is Error free (if not skip entry inputting)
			{
				cout << "Quantity Needed: ";
				istr >> qtyN;
				if (istr.fail() == false)
				{
					qtyNeeded(qtyN);
				}
				else
					err_.message("Invalid Quantity Needed Entry");
			}
		}


		return istr;

	}

	
}