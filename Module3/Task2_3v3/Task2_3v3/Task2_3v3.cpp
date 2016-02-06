#include <iostream>
#include <queue>
#include <stack>

struct BinaryNode
{
	int data;
	BinaryNode* left; // NULL, ���� ���.
	BinaryNode* right; // NULL, ���� ���.
};

void initBinaryNode(BinaryNode&, int);     // ������������� ��������

typedef BinaryNode* pBinaryNode;            // ��� �������� ��������� �� ������
void insertBinaryTree(pBinaryNode&, int);  // ������� �������� � ������


void traverseDownUpWithoutRecursion(BinaryNode*); // ����� ����� ����� nonrecursion

int main()
{
	// N - ���������� ��������� � ������
	size_t N;
	std::cin >> N;

	// buf - ����� ��� ����������
	int buf;
	std::cin >> buf;

	// ������� ������
	BinaryNode* node;
	node = new BinaryNode;
	initBinaryNode(*node, buf);

	// ������ ���������� �������� � ��������� � ������
	for (size_t i = 1; i < N; ++i)
	{
		std::cin >> buf;
		insertBinaryTree(node, buf);
	}

	// ����� ������
	
	traverseDownUpWithoutRecursion(node);

	return 0;
}

void initBinaryNode(BinaryNode& in, int data)
{
	in.data = data;
	in.left = NULL;
	in.right = NULL;
}

void insertBinaryTree(pBinaryNode& in, int data)
{
	// ����������� ������� �������� � �������� ������ ��������
	// ������� �������� �������.

	if (in == NULL)
	{
		in = new BinaryNode;
		initBinaryNode(*in, data);
		return;
	}

	// ���� ����� ���� >= ,�� �������� ��� � ������ ���������, ����� � �����
	if (data >= in->data)
		insertBinaryTree(in->right, data);
	else
		insertBinaryTree(in->left, data);
}



void traverseDownUpWithoutRecursion(BinaryNode* root)
{
	// ����� ��������� ������� ������ ����,
	// �.�. ������� ���������� ����, ����� ����� � ������ ����������.

	std::stack<BinaryNode*> one;
	std::stack<BinaryNode*> two;

	one.push(root);
	while (!one.empty())
	{
		BinaryNode* node = one.top();
		one.pop();
		two.push(node);

		if (node->left != NULL)
			one.push(node->left);

		if (node->right != NULL)
			one.push(node->right);
	}

	while (!two.empty())
	{
		std::cout << two.top()->data << " ";
		two.pop();
	}
}