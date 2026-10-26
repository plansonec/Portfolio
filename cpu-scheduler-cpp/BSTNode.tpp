template <class key_t, class val_t>
BSTNode<key_t, val_t>::BSTNode(const key_t& key, const val_t& value)

{
this->key = key;
    this->value = value;
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->parent = nullptr;
}

template <class key_t, class val_t>
const key_t& BSTNode<key_t, val_t>::getKey() const
{
    return key;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setKey(const key_t& newKey)
{
    key = newKey;
}

template <class key_t, class val_t>
const val_t& BSTNode<key_t, val_t>::getValue() const
{
    return value;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setValue(const val_t& newValue)
{
    value = newValue;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getLeftChild() const
{
    return leftChild;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setLeftChild(BSTNode<key_t, val_t>* child)
{
   leftChild = child;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getRightChild() const
{
    return rightChild;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setRightChild(BSTNode<key_t, val_t>* child)
{
    rightChild = child;
}

template <class key_t, class val_t>
BSTNode<key_t, val_t>* BSTNode<key_t, val_t>::getParent() const
{
    return parent;
}

template <class key_t, class val_t>
void BSTNode<key_t, val_t>::setParent(BSTNode<key_t, val_t>* newParent)
{
    parent = newParent;
}

