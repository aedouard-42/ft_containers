//#define STD

#ifdef STD
 #include <vector>
 #include <map>
 #include <stack>
 namespace ft = std;
#else
 #include "vector/vector.hpp"
 #include "map/map.hpp"
 #include "stack/stack.hpp"
 #include "utils/pair.hpp"
 #include "utils/is_integral.hpp"
 #include "utils/enable_if.hpp"
 #include "utils/iterators_traits.hpp"
 #include "utils/reverse_iterator.hpp"
 #include "utils/lexicographical_compare.hpp"
#endif

#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <list>

class Observable {
	public:
		int _data;
		Observable() { _data = 0; std::cout << "Instance of Observable created." << std::endl; }
		Observable(int data): _data(data) { std::cout << "Instance of Observable created." << std::endl; }
		Observable(Observable const & src) { *this = src; }
		//~Observable() { std::cout << "Instance of Observable destroyed." << this->_data << std::endl; }
		Observable &operator=(Observable const &rhs) { _data = rhs._data; return *this; }
};
std::ostream &operator<<(std::ostream & os, const Observable &obs) {
	os << obs._data;
	return os;
}

template<class T>
void display_vector(ft::vector<T> vector)
{
	std::cout << std::endl;
	std::cout << "vector display" << std::endl;
	for (unsigned int i = 0; i < vector.size(); i++)
	{std::cout << vector[i] << std::endl;}
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;

	//default constructor

	/*********************************** PAIR TESTS **********************************/

	ft::pair<int , std::string>p1;
	std::cout << p1.first << std::endl;
	std::cout << p1.second << std::endl;
	// // assignation constructor
	ft::pair <int , std::string>p2(42,"abc");
	std::cout << p2.first << std::endl;
	std::cout << p2.second << std::endl;
	// copy constructor
	ft::pair <int , std::string>p4(p2);
	std::cout << p4.first << std::endl;
	std::cout << p4.second << std::endl;
	// // operator=
	p4=p1;
	std::cout << p4.first << std::endl;
	std::cout << p4.second << std::endl;
	//comparison operators :
	std::cout << (p2 == p4) << std::endl;
	std::cout << (p1 ==p4) << std::endl;
	// // !=
	std::cout << (p2 !=p1) << std::endl;
	std::cout << (p1 !=p4) << std::endl;
	ft::pair<int, int> p5 = ft::make_pair(12,13);
	std::cout << p5.first << std::endl;
	std::cout << p5.second << std::endl;

	/*********************************** IS INTEGRAL TESTS **********************************/

	std::cout << std::boolalpha;
 	std::cout << "char: " << ft::is_integral<char>::value << std::endl;
	std::cout << "int: " << ft::is_integral<int>::value << std::endl;
	std::cout << "float: " << ft::is_integral<float>::value << std::endl;
	std::cout << "long int: " << ft::is_integral<long int>::value << std::endl;


	/*********************************** VECTOR TESTS *************************************/


	const std::allocator<int> allocator_int;

	ft::vector<int> vector1;
	ft::vector<int> vector2(allocator_int);

	vector2.push_back(100);
	std::cout << vector2.back();
	vector2.push_back(42);
	std::cout << vector2.back();
	vector2.pop_back();
	
	std::cout << vector2.back();
	std::cout << vector2.size();
	std::cout << vector2.capacity();
	//display_vector(vector2);
	//vector2.reserve(99);
	//display_vector(vector2);
	// std::cout << vector2.size();
	// std::cout << vector2.capacity();
	vector2.push_back(43);
	vector2.push_back(44);
	vector2.push_back(45);
	vector2.push_back(46);
	vector2.push_back(47);
	vector2.push_back(48);
	display_vector(vector2);

	ft::vector<int>::iterator insert_test = vector2.insert(vector2.begin() + 2, 36);
	std::cout << "return value for insert test : " << *insert_test << std::endl;

	vector2.insert(vector2.begin(), 5, 77);
	vector2.insert(vector2.begin() + 2, 5, 33);
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector1.push_back(4);
	vector1.push_back(5);
	vector1.push_back(6);
	vector1.push_back(7);
	vector1.push_back(8);
	vector1.erase(vector1.begin());

	ft::vector<int>::iterator test = vector1.erase(vector1.begin() +2, vector1.begin() + 4);

	std::cout << "return value for erase : " << *test << std::endl;
	vector2.resize(36, 0);
	std::cout <<  "before insert capacity : :" << vector2.capacity() << std::endl;
	std::cout <<  "before insert size :" << vector2.size() << std::endl;
	std::cout <<  "before insert size : :" << vector2.size() << std::endl;
	std::cout <<  "before insert capacity : :" << vector2.capacity() << std::endl;
	display_vector(vector2);
	vector2.insert(vector2.begin(), vector1.begin(), vector1.end()); // problem for erase and insert if vector1.end() + 1 probably just undefined behavior
	std::cout <<  "after insert capacity : :" << vector2.capacity() << std::endl;
	std::cout <<  "after insert size : :" << vector2.size() << std::endl;
	std::cout <<  "before resize size :" << vector2.size() << std::endl;
	vector2.resize(36, 0);
	std::cout <<  "after resize capacity : :" << vector2.capacity() << std::endl;
	std::cout <<  "after resize size :" << vector2.size() << std::endl;
	display_vector(vector2);
	vector2.assign(4, 99);
	display_vector(vector2);

	Observable c1;
	Observable c2;

	ft::vector<Observable> vector3;
	const std::allocator<Observable> obs;
	ft::vector<Observable> vector4(obs);

	vector4.push_back(c1);
	vector4.push_back(c2);
	vector4.push_back(c1);
	vector3.push_back(c1);
	vector3.push_back(c2);

	vector3.insert(vector3.end(), c2);
	std::cout <<  "before insert :" << vector3.capacity() << std::endl;
	std::cout <<  "before insert size :" << vector3.size() << std::endl;
	vector3.insert(vector3.end(), 5, c2);
	std::cout <<  "after insert capacity :" << vector3.capacity() << std::endl;
	std::cout <<  "after insert  size :" << vector3.size() << std::endl;

	vector3.insert(vector3.begin() +1, vector4.begin(), vector4.end());
	display_vector(vector3);
	vector3.erase(vector3.begin());
	vector3.erase(vector3.begin(), vector3.end() - 1);
	
	display_vector(vector3);
	std::cout << "vector3 capacity :" << vector3.capacity() << std::endl;
	std::cout << "vector3 size :" << vector3.size() << std::endl;

	vector3.insert(vector3.begin(), 17, Observable(1));
	std::cout << "vector 3 size before resize :" << vector3.size() <<  std::endl;
	std::cout << "vector 3 capacity before resize :" << vector3.capacity() <<  std::endl;
	vector3.resize(33, Observable());
	std::cout << "vector 3 size after resize :" << vector3.size() <<  std::endl;
	std::cout << "vector 3 capacity after resize :" << vector3.capacity() <<  std::endl;

	display_vector(vector3);
	display_vector(vector1);
	display_vector(vector2);
	vector1.swap(vector2);
	display_vector(vector1);
	display_vector(vector2);
	std::cout << *vector1.rbegin() << std::endl; 

	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';

	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';


	{
	ft::vector<int> foo,bar;

	foo.push_back(100);
	foo.push_back(200);

	bar.push_back(11);
	bar.push_back(22);
	bar.push_back(33);


	ft::vector<int>::const_iterator tmp = foo.begin(); //tmp iterates through foo
	ft::vector<int>::const_iterator tmp2 = bar.begin(); //tmp2 iterates through bar

	std::cout <<"tmp before swap :" <<*tmp << std::endl;
	std::cout << "tmp2 before swap : " <<*tmp2 << std::endl;


	swap(bar, foo); //tmp iterates through bar
					//tmp2 iterates through foo

	std::cout <<"tmp after swap :" <<*tmp << std::endl;
	std::cout << "tmp2 after swap : " <<*tmp2 << std::endl;


	ft::vector<int>	other;

	other.push_back(73);
	other.push_back(173);
	other.push_back(763);
	other.push_back(73854);
	other.push_back(74683);
	other.push_back(753);

	ft::vector<int>::const_iterator tmp3 = other.begin(); // tmp3 iterates through other

	std::cout << "foo contains:\n";
	for (ft::vector<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		std::cout << *it << '\n';

	std::cout << "bar contains:\n";
	for (ft::vector<int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << *it << '\n';


	std::cout << "iter through bar contains :" << std::endl;
	while(tmp != bar.end())
	{
		std::cout << *tmp << '\n';
		tmp++;
	}
	tmp--;

	(void)tmp2;

	std::cout << "tmp2 : "<< *tmp2 << std::endl;

	while(tmp2 != foo.end())
	{
		std::cout << *tmp2 << '\n';
		tmp2++;
	}
	tmp2--;

	swap(other, foo); //tmp2 iterates through other
					//tmp3 iterates throught foo
	display_vector(other);
	display_vector(foo);
	display_vector(bar);
	while(tmp != bar.begin())
	{
		std::cout << *tmp << '\n';
		tmp--;
	}
	std::cout << *tmp << '\n';

	while(tmp2 != other.begin())
	{
		std::cout << *tmp2 << '\n';
		tmp2--;
	}
		std::cout << *tmp2 << '\n';

	while(tmp3 != foo.end())
	{
		std::cout << *tmp3 << '\n';
		tmp3++;
	}
	tmp3--;

	swap(bar, foo);
	swap(foo, bar);
	swap(bar, foo); //tmp3 iterates through bar
				//tmp iterates through foo

	display_vector(other);
	display_vector(foo);
	display_vector(bar);

	while(tmp != foo.end())
	{
		std::cout << *tmp << '\n';
		tmp++;
	}

	while(tmp2 != other.end())
	{
		std::cout << *tmp2 << '\n';
		tmp2++;
	}

	while(tmp3 != bar.begin())
	{
		std::cout << *tmp3 << '\n';
		tmp3--;
	}
		std::cout << *tmp3 << '\n';

}
	/////////////////MAP TESTS////////////////////////////////////////////////////////////
	ft::map<int, int > int_map;
	ft::map<int , int>::iterator int_map_iterator;
	ft::map<int , int>::reverse_iterator rev_int_map_iterator;
	rev_int_map_iterator = int_map.rbegin();

	int nb_keys = 70;
	int keys[nb_keys];
	ft::pair <int , int> arraypair[nb_keys];

	srand(1);

	for (int i = 0; i < nb_keys; i++)
	{
		keys[i] = ( rand() % nb_keys);
		std::cout << keys[i] << std::endl;
	}
	for (int i = 0; i < nb_keys; i++)
	{
		arraypair[i] = ft::pair<int, int>(keys[i], i);
	}
	for (int i = 0; i < nb_keys; i++)
	{
		int_map.insert(arraypair[i]);
	}

	for (int_map_iterator = int_map.begin() ; int_map_iterator != int_map.end(); int_map_iterator++)
	{
	    std::cout << int_map_iterator->first << " ";
	}
	for (rev_int_map_iterator = int_map.rbegin() ; rev_int_map_iterator != int_map.rend(); rev_int_map_iterator++)
    {
		std::cout << rev_int_map_iterator->first << " ";
    }
	std::cout << std::endl;

	std::list<ft::pair<const int , std::string> > lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(ft::pair<const int, std::string>(i, std::string((lst_size - i), i + 65)));
	ft::map<int, std::string> mp(lst.begin(), lst.end());

	mp.erase(++mp.begin());
	mp.erase(mp.begin());
	mp.erase(--mp.end());

	mp.erase(mp.begin(), ++(++(++mp.begin())));
	std::cout << int_map.size() << std::endl;

	

	ft::map<char,int> mymap;

	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;

  	std::cout << "mymap contains:\n";
  	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    	std::cout << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a']=1101;
	mymap['b']=2202;

  	std::cout << "mymap contains:\n";
  	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';


	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	//int_map.printTree();
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	int_map.erase(22);
	int_map.erase(9);
	int_map.erase(12);
	int_map.erase(43);
	int_map.print_tree_ascii();

}
