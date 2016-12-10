//Milestone 4
//CustomMade.cpp
//Shaun Richardson
//110392156
//srichardson6@myseneca.ca

#include <iomanip>
#include "CustomMade.h"

namespace ict 
{

	CustomMade::CustomMade(): OnShelf('C')
	{
	}

	const Date& CustomMade::delivery() const
	{
		return delivery_;
	}

	void CustomMade::delivery(const Date& value)
	{
		delivery_ = value;
	}

	std::fstream& CustomMade::store(std::fstream& file, bool addNewLine) const
	{
		OnShelf::store(file, false);
		file << ",";
		delivery_.write(file);

		if (addNewLine)
		{
			file << std::endl;
		}
		return file;
	}

	std::fstream& CustomMade::load(std::fstream& file)
	{
		OnShelf::load(file);
		
		delivery_.read(file);

		return file;
	}

	std::ostream& CustomMade::display(std::ostream& os, bool linear) const
	{
		if (err_.isClear() == false)
		{
			os << err_.message();
			return os;
		}
		else if (linear)
		{
			os << std::setfill(' ') << std::left << std::setw(MAX_SKU_LEN) << sku() << "|"
				<< std::setw(20) << name() << "|"
				<< std::right << std::setprecision(2) << std::setw(7) << std::showpoint << std::fixed << cost() << '|';
			if (taxed())   //If good is taxed (true)
			{
				os << " t |";
			}
			else
			{
				os << "   |";
			}
			os << std::setw(4) << quantity() << '|'
				<< std::setw(4) << qtyNeeded() << '|'
				<< delivery() << std::endl;
		}
		else
		{
			os << "Sku: " << sku() << std::endl;
			os << "Name: " << name() << std::endl;
			os << "Price: " << price() << std::endl;
			if (taxed() == true)
			{
				os << "Price after tax: " << (TAX + 1) * price() << std::endl;
			}
			else
			{
				os << "Price after tax: N/A" << std::endl;
			}

			os << "Quantity On Hand: " << quantity() << std::endl;
			os << "Quantity Needed: " << qtyNeeded() << std::endl;
				
				os << "delivery date: " << delivery();
		}
		return os;
	}

	std::istream& CustomMade::conInput(std::istream& is)
	{
		
		OnShelf::conInput(is);

		if (err_.isClear())
		{
			std::cout << "delivery date (YYYY/MM/DD): ";
			Date temp;
			is >> temp;

			if (temp.bad())
			{
				if (temp.errCode() == CIN_FAILED)
				{
					err_.message("Invalid Date Entry");
				}
				else if (temp.errCode() == YEAR_ERROR)
				{
					err_.message("Invalid Year in Date Entry");
				}
				else if (temp.errCode() == MON_ERROR)
				{
					err_.message("Invalid Month in Date Entry");
				}
				else if (temp.errCode() == DAY_ERROR)
				{
					err_.message("Invalid Day in Date Entry");
				}
				is.setstate(std::ios::failbit);
			}
			else
			{
				delivery(temp);
			}
		}
		return is;
	}
}
