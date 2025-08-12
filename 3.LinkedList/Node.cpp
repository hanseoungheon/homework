#include "Node.h"

Node::Node()
	//:data(0), next(nullptr)
	:Node(0)
{

}

Node::Node(int data)
	: data(data),next(nullptr)
{

}

int Node::GetData() const
{
	return data;
}

void Node::SetData(const int data)
{
	this->data = data;
}
