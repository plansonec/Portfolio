template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::BSTMultimap()
{
    sentinel = nullptr;
    root = sentinel;
    numItems = 0;
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::insert(const key_t& key, const val_t& value)
{
    BSTNode<key_t, val_t>* newNode = new BSTNode<key_t, val_t>(key, value);
    newNode->setLeftChild(sentinel);
    newNode->setRightChild(sentinel);
    newNode->setParent(sentinel);
    insertNode(newNode);
    numItems++;
}

template <class key_t, class val_t>void BSTMultimap<key_t, val_t>::insertNode(BSTNode<key_t, val_t>* node)
{
    BSTNode<key_t, val_t>* current = root;
    BSTNode<key_t, val_t>* parent = sentinel;

    while (current != sentinel)
    {
        parent = current;
        if (node->getKey() < current->getKey())
        {
            current = current->getLeftChild();
        }
        else
        {
            current = current->getRightChild();
        }
    }

    node->setParent(parent);

    if (parent == sentinel)
    {
        root = node;
    }
    else if (node->getKey() < parent->getKey())
    {
        parent->setLeftChild(node);
    }
    else
    {
        parent->setRightChild(node);
    }
}

template <class key_t, class val_t>
int BSTMultimap<key_t, val_t>::getSize() const
{
    return numItems;
}

template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::isEmpty() const
{
    return numItems == 0;
}

template <class key_t, class val_t>
BSTMultimap<key_t, val_t>::~BSTMultimap()
{
    clear();
}

template <class key_t, class val_t>
void BSTMultimap<key_t, val_t>::clear()
{
    if (root == sentinel)
    {
        return;
    }

    queue<BSTNode<key_t, val_t>*> q;
   q.push(root);

    while (!q.empty())
   {
        BSTNode<key_t, val_t>* current = q.front();
        q.pop();

        if (current->getLeftChild() != sentinel)
        {
            q.push(current->getLeftChild());
        }
        if (current->getRightChild() != sentinel)
        {
            q.push(current->getRightChild());
        }

        delete current; 
    }

    root = sentinel;
    numItems = 0;
}

template <class key_t, class val_t>
bool BSTMultimap<key_t, val_t>::contains(const key_t& key) const
{
    BSTNode<key_t, val_t>* current = root;

    while (current != sentinel)
    {
        if (key == current->getKey())
        {
            return true; 
        }
        else if (key < current->getKey())
        {
            current = current->getLeftChild();
        }
        else
        {
            current = current->getRightChild();
        }
    }

   return false;
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::remove(const BSTForwardIterator<key_t, val_t>& pos)
{
    BSTNode<key_t, val_t>* z = pos.current;

    if (z == sentinel)
    {
        return BSTForwardIterator<key_t, val_t>(sentinel, sentinel);
    }

    BSTForwardIterator<key_t, val_t> nextIter = pos;
    nextIter.next(); 

    if (z->getLeftChild() == sentinel)
    {
        BSTNode<key_t, val_t>* right = z->getRightChild();

        if (z->getParent() == sentinel) 
    {
            root = right;
        }
        else if (z == z->getParent()->getLeftChild()) 
        {
            z->getParent()->setLeftChild(right);
        }
        else 
        {
            z->getParent()->setRightChild(right);
        }

        if (right != sentinel) 
        {
            right->setParent(z->getParent());
        } 
    }
    else if (z->getRightChild() == sentinel)
    {
        BSTNode<key_t, val_t>* left = z->getLeftChild();

        if (z->getParent() == sentinel) 
        {
            root = left;
        }
        else if (z == z->getParent()->getLeftChild()) 
        {
            z->getParent()->setLeftChild(left);
        }
        else 
        {
            z->getParent()->setRightChild(left);
        }

        if (left != sentinel) 
        {
            left->setParent(z->getParent());
        }
    }
    else
   {
        BSTNode<key_t, val_t>* y = z->getRightChild();
        while (y->getLeftChild() != sentinel)
        {
            y = y->getLeftChild();
        }

        if (y->getParent() != z)
        {
            BSTNode<key_t, val_t>* yRight = y->getRightChild();

            if (y == y->getParent()->getLeftChild()) 
            {
                y->getParent()->setLeftChild(yRight);
            }
            else 
            {
                y->getParent()->setRightChild(yRight);
            }

            if (yRight != sentinel) 
            {
                yRight->setParent(y->getParent());
            }

            y->setRightChild(z->getRightChild());
           y->getRightChild()->setParent(y);
        }

        if (z->getParent() == sentinel) 
        {
            root = y;
        }
        else if (z == z->getParent()->getLeftChild()) 
        {
            z->getParent()->setLeftChild(y);
        }
        else 
        {
            z->getParent()->setRightChild(y);
        }

        y->setParent(z->getParent());
        y->setLeftChild(z->getLeftChild());
        y->getLeftChild()->setParent(y);
    }

    delete z;
    numItems--;

    return nextIter;
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findFirst(const key_t& key) const
{
    BSTNode<key_t, val_t>* current = root;
    BSTNode<key_t, val_t>* result = sentinel;

    while (current != sentinel)
    {
        if (key == current->getKey())
      {
            result = current;       // Save this candidate
            current = current->getLeftChild(); // Try going left
        }
        else if (key < current->getKey())
        {
            current = current->getLeftChild();
        }
        else
        {
            current = current->getRightChild();
        }
    }

   return BSTForwardIterator<key_t, val_t>(result, sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::findLast(const key_t& key) const
{
    BSTNode<key_t, val_t>* current = root;
    BSTNode<key_t, val_t>* result = sentinel;

    while (current != sentinel)
    {
        if (key == current->getKey())
        {
            result = current;        // Save this candidate
            current = current->getRightChild(); // Try going right
        }
        else if (key < current->getKey())
        {
            current = current->getLeftChild();
        }
        else
        {
            current = current->getRightChild();
         }
   }

    return BSTForwardIterator<key_t, val_t>(result, sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMin() const
{
    if (numItems == 0)
    {
        return BSTForwardIterator<key_t, val_t>(sentinel, sentinel);
    }

    BSTNode<key_t, val_t>* current = root;

    while (current->getLeftChild() != sentinel)
    {
        current = current->getLeftChild();
    }

    return BSTForwardIterator<key_t, val_t>(current, sentinel);
}

template <class key_t, class val_t>
BSTForwardIterator<key_t, val_t> BSTMultimap<key_t, val_t>::getMax() const
{
    if (numItems == 0)
    {
        return BSTForwardIterator<key_t, val_t>(sentinel, sentinel);
    }

    BSTNode<key_t, val_t>* current = root;
    while (current->getRightChild() != sentinel)
    {
        current = current->getRightChild();
    }

    return BSTForwardIterator<key_t, val_t>(current, sentinel);
}