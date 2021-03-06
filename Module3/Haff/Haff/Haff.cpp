#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>

using namespace std;

template<typename DataType, typename Frequency> class Hufftree
{
public:
	template<typename InputIterator>
	Hufftree(InputIterator begin, InputIterator end);
	~Hufftree() { delete tree; }
	template<typename InputIterator>
	std::vector<bool> encode(InputIterator begin, InputIterator end);
	std::vector<bool> encode(DataType const& value)
	{
		return encoding[value];
	}
	template<typename OutputIterator>
	void decode(std::vector<bool> const& v, OutputIterator iter);
private:
	class Node;
	Node* tree;
	typedef std::map<DataType, std::vector<bool> > encodemap;
	encodemap encoding;
	class NodeOrder;
};
template<typename DataType, typename Frequency>
struct Hufftree<DataType, Frequency>::Node
{
	Frequency frequency;
	Node* leftChild;
	union
	{
		Node* rightChild; // if leftChild != 0
		DataType* data;  // if leftChild == 0
	};
	Node(Frequency f, DataType d) :
		frequency(f),
		leftChild(0),
		data(new DataType(d))
	{
	}
	Node(Node* left, Node* right) :
		frequency(left->frequency + right->frequency),
		leftChild(left),
		rightChild(right)
	{
	}
	~Node()
	{
		if (leftChild)
		{
			delete leftChild;
			delete rightChild;
		}
		else
		{
			delete data;
		}
	}
	void fill(std::map<DataType, std::vector<bool> >& encoding, std::vector<bool>& prefix)
	{
		if (leftChild)
		{
			prefix.push_back(0);
			leftChild->fill(encoding, prefix);
			prefix.back() = 1;
			rightChild->fill(encoding, prefix);
			prefix.pop_back();
		}
		else
			encoding[*data] = prefix;
	}
};
template<typename DataType, typename Frequency>
template<typename InputIterator>
Hufftree<DataType, Frequency>::Hufftree(InputIterator begin, InputIterator end) :tree(0)
{
	std::priority_queue<Node*, std::vector<Node*>, NodeOrder> pqueue;
	while (begin != end)
	{
		Node* dataNode = new Node(begin->second, begin->first);
		pqueue.push(dataNode);
		++begin;
	}
	while (!pqueue.empty())
	{
		Node* top = pqueue.top();
		pqueue.pop();
		if (pqueue.empty())
		{
			tree = top;
		}
		else
		{
			Node* top2 = pqueue.top();
			pqueue.pop();
			pqueue.push(new Node(top, top2));
		}
	}
	std::vector<bool> bitvec;
	tree->fill(encoding, bitvec);

}
template<typename DataType, typename Frequency>
struct Hufftree<DataType, Frequency>::NodeOrder
{
	bool operator()(Node* a, Node* b)
	{
		if (b->frequency < a->frequency)
			return true;
		if (a->frequency < b->frequency)
			return false;

		if (!a->leftChild && b->leftChild)
			return true;
		if (a->leftChild && !b->leftChild)
			return false;

		if (a->leftChild && b->leftChild)
		{
			if ((*this)(a->leftChild, b->leftChild))
				return true;
			if ((*this)(b->leftChild, a->leftChild))
				return false;
			return (*this)(a->rightChild, b->rightChild);
		}

		return *(a->data) < *(b->data);

	}
};
template<typename DataType, typename Frequency>
template<typename InputIterator>
std::vector<bool> Hufftree<DataType, Frequency>::encode(InputIterator begin, InputIterator end)
{
	std::vector<bool> result;
	while (begin != end)
	{
		typename encodemap::iterator i = encoding.find(*begin);
		result.insert(result.end(), i->second.begin(), i->second.end());
		++begin;
	}
	return result;
}

template<typename DataType, typename Frequency>
template<typename OutputIterator>
void Hufftree<DataType, Frequency>::decode(std::vector<bool> const& v, OutputIterator iter)
{
	Node* node = tree;
	for (std::vector<bool>::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		node = *i ? node->rightChild : node->leftChild;
		if (!node->leftChild)
		{
			*iter++ = *(node->data);
			node = tree;
		}
	}
}

ostream& operator<<(ostream& os, vector<bool> vec)
{
	copy(vec.begin(), vec.end(), ostream_iterator<bool>(os, ""));
	return os;
}

void compress_string(const string &source, string &compressed){
	std::stringstream str;
	std::map<char, double> frequencies;
	frequencies['e'] = 0.114864;
	frequencies['a'] = 0.078828;
	frequencies['t'] = 0.067567;
	frequencies['i'] = 0.056306;
	frequencies['n'] = 0.065315;
	frequencies['o'] = 0.049549;
	frequencies['s'] = 0.047297;
	frequencies['r'] = 0.054054;
	frequencies['l'] = 0.027027;
	frequencies['d'] = 0.020270;
	frequencies['h'] = 0.024774;
	frequencies['c'] = 0.024774;
	frequencies['u'] = 0.013513;
	frequencies['m'] = 0.013513;
	frequencies['f'] = 0.022522;
	frequencies['p'] = 0.020270;
	frequencies['y'] = 0.011261;
	frequencies['g'] = 0.018018;
	frequencies['w'] = 0.024774;
	frequencies['v'] = 0.006756;
	frequencies['b'] = 0.006756;
	frequencies['k'] = 0.006756;
	frequencies['x'] = 0.002252;
	frequencies['L'] = 0.006756;
	frequencies['q'] = 0.004504;
	frequencies['N'] = 0.002252;
	frequencies['S'] = 0.006756;
	frequencies['E'] = 0.006756;
	frequencies['T'] = 0.002252;
	frequencies['F'] = 0.002252;
	frequencies['U'] = 0.002252;
	frequencies['I'] = 0.002252;
	frequencies['M'] = 0.002252;
	frequencies['1'] = 0.002252;
	frequencies['.'] = 0.006756;
	frequencies['_'] = 0.162162;
	frequencies['2'] = 0.002252;
	frequencies[':'] = 0.004504;
	frequencies['`'] = 0.002252;
	Hufftree<char, double> hufftree(frequencies.begin(), frequencies.end());
	vector<bool> encoded = hufftree.encode(source.begin(), source.end());
	str << encoded << "\n";
	compressed = str.str();
}
void decompress_string(const string &compressed, string &result){
	std::stringstream str;
	std::map<char, double> frequencies;
	frequencies['e'] = 0.114864;
	frequencies['a'] = 0.078828;
	frequencies['t'] = 0.067567;
	frequencies['i'] = 0.056306;
	frequencies['n'] = 0.065315;
	frequencies['o'] = 0.049549;
	frequencies['s'] = 0.047297;
	frequencies['r'] = 0.054054;
	frequencies['l'] = 0.027027;
	frequencies['d'] = 0.020270;
	frequencies['h'] = 0.024774;
	frequencies['c'] = 0.024774;
	frequencies['u'] = 0.013513;
	frequencies['m'] = 0.013513;
	frequencies['f'] = 0.022522;
	frequencies['p'] = 0.020270;
	frequencies['y'] = 0.011261;
	frequencies['g'] = 0.018018;
	frequencies['w'] = 0.024774;
	frequencies['v'] = 0.006756;
	frequencies['b'] = 0.006756;
	frequencies['k'] = 0.006756;
	frequencies['x'] = 0.002252;
	frequencies['L'] = 0.006756;
	frequencies['q'] = 0.004504;
	frequencies['N'] = 0.002252;
	frequencies['S'] = 0.006756;
	frequencies['E'] = 0.006756;
	frequencies['T'] = 0.002252;
	frequencies['F'] = 0.002252;
	frequencies['U'] = 0.002252;
	frequencies['I'] = 0.002252;
	frequencies['M'] = 0.002252;
	frequencies['1'] = 0.002252;
	frequencies['.'] = 0.006756;
	frequencies['_'] = 0.162162;
	frequencies['2'] = 0.002252;
	frequencies[':'] = 0.004504;
	frequencies['`'] = 0.002252;
	Hufftree<char, double> hufftree(frequencies.begin(), frequencies.end());
	vector<bool> encoded;
	for (int i = 0; i < compressed.size(); i++){
		if (compressed.at(i) == '1'){
			encoded.push_back(1);
		}
		else if (compressed.at(i) == '0'){
			encoded.push_back(0);
		}
		else{

		}
	}
	hufftree.decode(encoded, std::back_inserter(result));
}



/*int main()
{
	string out = "";
	string out2 = "";
	string source = "Newton`s_Law_of_Software_Engineering_continues";
	cout << source << endl;
	compress_string(source, out);
	cout << out << endl;
	decompress_string(out, out2);
	cout << out2 << endl;
	cin.get();
}
*/



