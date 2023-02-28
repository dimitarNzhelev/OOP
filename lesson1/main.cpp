#include <iostream>

using namespace std;

struct vector_t
{
    int *data;
    size_t size;
    size_t capacity;
};

/**
 * @brief Function for creating new object of type vector_t
 *
 * @param size
 * @return struct vector_t*
 */
struct vector_t *init()
{
    struct vector_t *vector = new vector_t;
    vector->capacity = 2;
    vector->data = new int[vector->capacity];
    vector->size = 0;
    return vector;
}

/**
 * @brief Function for freeing the memory allocated for a vector
 *
 * @param v
 */
void deleteVector(vector_t *vector)
{
    // for (size_t i = 0; i < vector->capacity; i++)
    // {
    //     delete vector->data[i];
    // }
    delete[] vector->data;
    delete vector;
}

/**
 * @brief Resizes the vector with double the current capacity
 *
 * @param vector
 */
void resize(vector_t *vector)
{
    int *newArray = new int[vector->capacity * 2];
    for (int i = 0; i < vector->size; i++)
    {
        newArray[i] = vector->data[i];
    }
    delete[] vector->data;
    vector->data = newArray;
}

/**
 * @brief Function for appending new element to the array
 *
 * @param vector
 * @param v
 */
void add(vector_t *vector, int value)
{
    if (vector->size == vector->capacity)
    {
        resize(vector);
    }
    vector->data[vector->size] = value;
    vector->size++;
}

//============================================================================
// HOMEWORK
//============================================================================
/**
 * @brief Create exact clone of a vector
 *
 * @param vector
 * @return struct vector_t*
 */
struct vector_t *clone(struct vector_t *vector)
{
    struct vector_t *cloneVector = init();
    cloneVector->capacity = vector->capacity;
    cloneVector->size = vector->size;
    cloneVector->data = new int[vector->capacity];
    for (int i = 0; i < vector->size; i++)
    {
        cloneVector->data[i] = vector->data[i];
    }
    return cloneVector;
};

/**
 * @brief Removes the last element of a vector
 *
 * @param vector
 * @return struct vector_t*
 */
struct vector_t *removeLast(struct vector_t *vector)
{
    int *newData = new int[vector->size - 1];
    for (int i = 0; i < vector->size - 1; i++)
    {
        newData[i] = vector->data[i];
    }
    delete[] vector->data;
    vector->data = newData;
    delete[] newData;
    vector->size--;
    return vector;
};

/**
 * @brief Retrieves the element at the provided index
 *
 * @param vector
 * @param index
 * @return int
 */
int at(struct vector_t *vector, size_t index)
{
    if (index < vector->size)
    {
        return vector->data[index];
    }
};

int main()
{
    // int, float, char, bool - c
    // int, double, float, char, string, bool, signed, unsigned, short, long
    struct vector_t *vector = init();
    add(vector, 1);
    add(vector, 2);
    add(vector, 3);
    add(vector, 4);
    removeLast(vector);
    for (int i = 0; i < vector->size; i++)
    {
        cout << vector->data[i] << endl;
    }
    return 0;
}