template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t>::BSTForwardIterator(BSTNode<key_t, val_t>* node, BSTNode<key_t, val_t>* sentinel)
{
   current = node;
   this->sentinel = sentinel;
}

template <class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::next()
{
    if (current == sentinel) return;

    if (current->getRightChild() != sentinel)
    {
        current = current->getRightChild();

        while (current->getLeftChild() != sentinel)
        {
            current = current->getLeftChild();
        }
    }
    else
    {
        BSTNode<key_t, val_t>* parent = current->getParent();

        while (parent != sentinel && current == parent->getRightChild())
        {
            current = parent;
            parent = parent->getParent();
        }

        current = parent;
    }
}

template <class key_t, class val_t>
bool BSTForwardIterator<key_t, val_t>::isPastEnd() const
{
   return current == sentinel;
}

template <class key_t, class val_t>
const key_t& BSTForwardIterator<key_t, val_t>::getKey() const
{
   return current->getKey();
}

template <class key_t, class val_t>
const val_t& BSTForwardIterator<key_t, val_t>::getValue() const
{
   return current->getValue();
}

template <class key_t, class val_t>
void BSTForwardIterator<key_t, val_t>::setValue(const val_t& newVal)
{
   current->setValue(newVal);
}