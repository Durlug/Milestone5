#include <cstring>
#include <iostream>
#include <utility>
#include "wpgeneral.h"
#include "Good.h"
using namespace std;
namespace ict {

	//Constructor 
	Good::Good(char* sku, char* name, double price, int qtyNeeded, bool tax)
	{
		strncpy(sku_, sku, MAX_SKU_LEN);

		int len = strlen(name);
		name_ = new char[len + 1];       //Allocating enough memory to hold the name in name_ pointer
		name_ = name;

		quantity_ = 0;
		qtyNeeded_ = qtyNeeded;
		price_ = price;
		taxed_ = tax;
	}

	//Deconstructor
	Good::~Good()
	{
		delete[] name_;
	}

	//Copy Constructor

	Good::Good(const Good& other)
	{

		strncpy(sku_, other.sku_, MAX_SKU_LEN);
	

		int len;
		len = strlen(other.name_);
		name_ = new char[len + 1];
		strncpy(name_, other.name_, len + 1);

		this->price_ = other.price_;
		this->taxed_ = other.taxed_;
		this->quantity_ = other.quantity_;
		this->qtyNeeded_ = other.qtyNeeded_;

	}

	//Overloaded = operator (to prevent memory leaks)
	Good& Good::operator=(const Good& other)
	{
		//Check for Self Assignment
		if (this == &other)
		{
			return *this;
		}

		
		strncpy(sku_, other.sku_, MAX_SKU_LEN);

		int len;
		len = strlen(other.name_);
		name_ = new char[len + 1];
		strncpy(name_, other.name_, len + 1);

		this->price_ = other.price_;
		this->taxed_ = other.taxed_;
		this->quantity_ = other.quantity_;
		this->qtyNeeded_ = other.qtyNeeded_;

		return *this;
	}


	//Setter Definitions
	void Good::sku(char* barcode)
	{
		strncpy(sku_, barcode, MAX_SKU_LEN);
	}

	void Good::price(double price)
	{
		price_ = price;
	}

	void Good::name(char* name)
	{	
		int len;
		len = strlen(name);
		name_ = new char[len + 1];
		strncpy(name_, name, len + 1);
	}

	void Good::taxed(bool taxed)
	{
		taxed_ = taxed;
	}

	void Good::quantity(int quantity)
	{
		quantity_ = quantity;
	}

	void Good::qtyNeeded(int qtyNeeded)
	{
		qtyNeeded_ = qtyNeeded;
	}

	//Getter Definitions

	const char* Good::sku() const
	{
		return sku_;
	}

	double Good::price() const
	{
		return price_;
	}

	const char* Good::name() const
	{
		return name_;
	}

	bool Good::taxed() const
	{
		return taxed_;
	}

	int Good::quantity() const
	{
		return quantity_;
	}

	int Good::qtyNeeded() const
	{
		return qtyNeeded_;
	}

	double Good::cost() const
	{
		if (taxed_ == 0)
		{
			return price_;
		}
		else
			return price_ + taxed_;
	}

	//Member Operator Overloads

	bool Good::operator==(const char* character)
	{
		if (character != this->sku_)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	int Good::operator+=(int quantity)
	{
		quantity_ += quantity;
		return quantity_;
	}

	//Non-member Operator Overload
	double operator+=(double& good, const Good& other)
	{
		good += (other.cost() * other.quantity());
		return good;
	}

	//Non-member IO operator overloads
	std::ostream& operator<<(ostream& os, Good& other)
	{
		other.display(os, true);
		return os;
	}

	std::istream& operator>>(istream& is, Good& other)
	{
		other.conInput(is);
		return is;
	}

}