#include <iostream>
#include <queue>
#include <stack>

struct BinaryNode
{
	int data;
	BinaryNode* left; // NULL, если нет.
	BinaryNode* right; // NULL, если нет.
};

void initBinaryNode(BinaryNode&, int);     // Инициализация элемента

typedef BinaryNode* pBinaryNode;            // Для передачи указателя по ссылке
void insertBinaryTree(pBinaryNode&, int);  // Вставка элемента в дерево


void traverseDownUpWithoutRecursion(BinaryNode*); // Обход снизу вверх nonrecursion

int main()
{
	// N - количество элементов в дереве
	size_t N;
	std::cin >> N;

	// buf - число для добавления
	int buf;
	std::cin >> buf;

	// Зададим корень
	BinaryNode* node;
	node = new BinaryNode;
	initBinaryNode(*node, buf);

	// Вводим оставшиеся значения и добавляем в дерево
	for (size_t i = 1; i < N; ++i)
	{
		std::cin >> buf;
		insertBinaryTree(node, buf);
	}

	// Вывод дерева
	
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
	// Рекурсивная вставка элемента в бинарное дерево заданное
	// наивным порядком вставки.

	if (in == NULL)
	{
		in = new BinaryNode;
		initBinaryNode(*in, data);
		return;
	}

	// Если новый ключ >= ,то помещаем его в правое поддерево, иначе в левое
	if (data >= in->data)
		insertBinaryTree(in->right, data);
	else
		insertBinaryTree(in->left, data);
}



void traverseDownUpWithoutRecursion(BinaryNode* root)
{
	// вывод элементов методом сверху вниз,
	// т.е. вначале посещается узел, затем левое и правые поддеревья.

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