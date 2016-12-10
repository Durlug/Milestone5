//Milestone 4
//Good.h
//Shaun Richardson
//110392156
//srichardson6@myseneca.ca

#ifndef ICT_GOOD_H__
#define ICT_GOOD_H__

#include "ReadWritable.h"
#include "wpgeneral.h"

namespace ict
{
	class Good : public ReadWritable
	{
	protected:
		char sku_[MAX_SKU_LEN + 1];
		char* name_;
		double price_;
		bool taxed_;
		int quantity_;
		int qtyNeeded_;

	public:
		//Constructor
		Good();
		Good(const char* sku, const char* name, double price, int qtyNeeded, bool tax = true);

		//Copy Constructor
		Good(const Good& other);

		//Deconstructor
		virtual ~Good();

		//Overloading = operator
		Good& operator=(const Good& other);

		//Setters
		void sku(char* barcode);
		void price(double price);
		void name(char* name);
		void taxed(bool taxed);
		void quantity(int quantity);
		void qtyNeeded(int qtyNeeded);

		//Getters
		const char* sku() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		int qtyNeeded() const;
		double cost() const;

		//Member Operator Overloads
		bool operator==(const char*);
		int operator+=(int);
	};

		//Non-member operator Overloads
		double operator+=(double& good, const Good& other);

		//Non-member IO operator overloads
		std::ostream& operator <<(std::ostream& os, const Good& other);
		std::istream& operator >>(std::istream& is, Good& other);
}


#endif