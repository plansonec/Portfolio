template <class item_t>
ArrayList<item_t>::ArrayList()
{
    capacity = 10;
    size = 0;
    items = new item_t[capacity];
}

template <class item_t>
ArrayList<item_t>::ArrayList(int capacity)
{
    this->capacity = capacity;
    size = 0;
    items = new item_t[capacity];
}

template <class item_t>
ArrayList<item_t>::~ArrayList()
{
    delete[] items;
}

template <class item_t>
void ArrayList<item_t>::resize() 
{
    capacity *= 2; 
    item_t* newItems = new item_t[capacity];

    // Copy old items to new array
    for (int i = 0; i < size; i++) 
    {
        newItems[i] = items[i];
    }

    delete[] items; // Free the old array's memory
    items = newItems; // Point items to the new array
}

template <class item_t>
void ArrayList<item_t>::pushBack(const item_t& item)
{
    if (size >= capacity) 
    {
        resize();
    }

            items[size] = item;
        size++;
    }

template <class item_t>
void ArrayList<item_t>::popBack()
{
    size--;
}

template <class item_t>
const item_t& ArrayList<item_t>::getBack() const
{
    return items[size - 1];
}

template <class item_t>
void ArrayList<item_t>::pushFront(const item_t& item)
{
    if (size >= capacity) 
    {
        resize();
    }

    for (int i = size; i > 0; i--) 
    {
        items[i] = items[i - 1];
    }

    items[0] = item;
    size++;
}

template <class item_t>
void ArrayList<item_t>::popFront()
{
    for (int i = 0; i < size - 1; i++) 
    {
        items[i] = items[i + 1];
    }

    size--;
}

template <class item_t>
const item_t& ArrayList<item_t>::getFront() const
{
    return items[0];
}

template <class item_t>
const item_t& ArrayList<item_t>::getItem(int index) const
{
    return items[index];
}

template <class item_t>
void ArrayList<item_t>::setItem(int index, const item_t& item)
{
    items[index] = item;
}

template <class item_t>
void ArrayList<item_t>::insert(int index, const item_t& item)
{
    if (size >= capacity) 
    {
        resize();
    }

    for (int i = size; i > index; i--) 
    {
        items[i] = items[i - 1];
    }

    items[index] = item;
    size++;
}

template <class item_t>
void ArrayList<item_t>::remove(int index)
{
    for (int i = index; i < size - 1; i++) 
    {
        items[i] = items[i + 1];
    }

    size--;
}

template <class item_t>
int ArrayList<item_t>::getSize() const
{
    return size;
}

template <class item_t>
bool ArrayList<item_t>::isEmpty() const
{
    return size == 0;
}

template <class item_t>
int ArrayList<item_t>::getCapacity() const
{
    return capacity;
}