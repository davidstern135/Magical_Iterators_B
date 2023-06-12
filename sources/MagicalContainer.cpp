#include "MagicalContainer.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Check if a number is prime
bool isPrime(int num) {
    if (num < 2)
        return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}


namespace ariel {

    // MagicalContainer
    // Add the elements from mainElements vector to ascendingOrder vector in ascending order

    void MagicalContainer::addToAscendingOrder() {
        ascendingOrder.clear();
        for (auto itr = mainElements.begin(); itr != mainElements.end(); ++itr) {
            ascendingOrder.push_back(&(*itr));
        }
        // Sort the pointers in ascending order based on their pointed values
        sort(ascendingOrder.begin(), ascendingOrder.end(), [](int *a, int *b) { return *a < *b; });
    }

    // Add the side cross elements from mainElements vector to sideCrossOrder vector
    void MagicalContainer::addToSideCrossOrder() {
        sideCrossOrder.clear();
        auto start = mainElements.begin();
        auto end = --mainElements.end();

        while (start < end) {
            sideCrossOrder.push_back(&(*start));
            sideCrossOrder.push_back(&(*end));
            start++;
            end--;
        }
        if (start == end) {
            sideCrossOrder.push_back(&(*start));
        }
    }

    // Add the prime elements from mainElements vector to primeOrder vector
    void MagicalContainer::addToPrimeOrder() {
        primeOrder.clear();
        for (auto it = mainElements.begin(); it != mainElements.end(); ++it) {
            if (isPrime(*it)) {
                primeOrder.push_back(&(*it));
            }
        }
    }

    // Add a new element to the mainElements vector and update the secondary  containers
    void MagicalContainer::addElement(int element) {
        if (find(mainElements.begin(), mainElements.end(), element) != mainElements.end()) {
            cout << "This element already entered the container" << endl;
            return;
        }
        // Update the mainElements vector
        mainElements.push_back(element);

        // Update the secondary  containers
        addToAscendingOrder();
        addToSideCrossOrder();
        addToPrimeOrder();

    }

    // Remove an element from the mainElements vector and update the secondary containers
    void MagicalContainer::removeElement(int element) {
        auto it = find(mainElements.begin(), mainElements.end(), element);
        if (it == mainElements.end()) {
            throw runtime_error("This element cannot be located in the container");
        }
        // Remove the element from the mainElements vector
        mainElements.erase(it);

        // Update the secondary containers
        addToAscendingOrder();
        addToSideCrossOrder();
        addToPrimeOrder();

    }

    // Get the size of the mainElements vector
    int MagicalContainer::size() const {
        return mainElements.size();

    }

    // Get a copy of the mainElements vector
    vector<int> MagicalContainer::getElements() const {
        return mainElements;

    }

    // Constructor and copy constructor:

    // AscendingIterator constructor
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container)
            : container(container), ascendingIterator(container.ascendingOrder.begin()), index(0) {}

    // AscendingIterator copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
            : container(other.container), ascendingIterator(other.ascendingIterator), index(other.index) {}

    // SideCrossIterator constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
            : container(container), sideCrossIterator(container.sideCrossOrder.begin()), index(0) {}

    // SideCrossIterator copy constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
            : container(other.container), sideCrossIterator(other.sideCrossIterator), index(other.index) {}

    // SideCrossIterator constructor
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
            : container(container), primeIterator(container.primeOrder.begin()), index(0) {}

    // PrimeIterator copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
            : container(other.container), primeIterator(other.primeIterator), index(other.index) {}



    // Pre-increment operator

    // AscendingIterator pre-increment operator
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++() {
        if (ascendingIterator == container.ascendingOrder.end()) {
            throw runtime_error("you tried reaching a location that is out of the container.");
        }
        ++ascendingIterator;
        ++index;
        return *this;
        // Increment the iterator and index by one.
    }

    // SideCrossIterator pre-increment operator
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++() {
        if (sideCrossIterator == container.sideCrossOrder.end()) {
            throw runtime_error("you tried reaching a location that is out of the container.");
        }
        ++sideCrossIterator;
        ++index;
        return *this;
    }

    // PrimeIterator pre-increment operator
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if (primeIterator == container.primeOrder.end()) {
            throw runtime_error("you tried reaching a location that is out of the container.");
        }
        ++primeIterator;
        ++index;
        return *this;
        // Increment the iterator and index by one.
    }




    // Equality operator and inequality operator

    // AscendingIterator equality operator
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& other) const {
        return (&container == &other.container) && (index == other.index);
    }

    // AscendingIterator inequality operator
    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& other) const {
        return !(*this == other);
    }

    // SideCrossIterator equality operator
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const {
        // Check if the iterators are pointing at the same container and have the same index
        return (&container == &other.container) && (index == other.index);
    }


    // SideCrossIterator inequality operator
    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const {
        return !(*this == other);
    }


    // PrimeIterator equality operator
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& other) const {
        // Check if the iterators are pointing at the same container and have the same index
        return (&container == &other.container) && (index == other.index);
    }


    // PrimeIterator inequality operator
    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& other) const {
        return !(*this == other);
    }





    // Greater-then and less-then iterators.

    // Check if the current iterator is greater than the other iterator.
    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw invalid_argument("Iterators are pointing to two different containers");
        }
        // Compare the indexes  of the iterators.
        return index > other.index;

    }
    // Check if the current iterator is less than the other iterator.
    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw invalid_argument("Iterators are pointing to two different containers");
        }
        // Compare the indexes  of the iterators.
        return index < other.index;
    }


    // Check if the current iterator is greater than the other iterator.
    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw invalid_argument("Iterators are pointing to two different containers");
        }
        // Compare the indexes  of the iterators.
        return index > other.index;
    }
    // Check if the current iterator is less than the other iterator.
    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw invalid_argument("Iterators are pointing to two different containers");
        }
        // Compare the indexes  of the iterators.
        return index < other.index;
    }


    // Check if the current iterator is greater than the other iterator.
    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw invalid_argument("Iterators are pointing to two different containers");
        }
        // Compare the indexes  of the iterators.
        return index > other.index;
    }
    // Check if the current iterator is less than the other iterator.
    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw invalid_argument("Iterators are pointing to two different containers");
        }
        // Compare the indexes  of the iterators.
        return index < other.index;
    }


    // Assignment operator

    // Assign the iterator and index values from another iterator.
    MagicalContainer::AscendingIterator &
    MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other) {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw runtime_error("Iterators are pointing at different containers");
        }
        // Assign the iterator and index values from the other iterator.
        ascendingIterator = other.ascendingIterator;
        index = other.index;
        return *this;
    }

    // Assign the iterator and index values from the other iterator.
    MagicalContainer::SideCrossIterator &
    MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other) {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw runtime_error("Iterators are pointing at different containers");
        }
        // Assign the iterator and index values from another iterator.
        sideCrossIterator = other.sideCrossIterator;
        index = other.index;
        return *this;
    }

    // Assign the iterator and index values from the other iterator.
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other) {
        // Check if the iterators are pointing at different containers.
        if (&container != &other.container) {
            throw runtime_error("Iterators are pointing at different containers");
        }
        // Assign the iterator and index values from another iterator.
        primeIterator = other.primeIterator;
        index = other.index;
        return *this;
    }

    // Dereference operator

    // AscendingIterator dereference operator
    int MagicalContainer::AscendingIterator::operator*() const {
        if (ascendingIterator == container.ascendingOrder.end()) {
            throw out_of_range("Out of range");
        }
        return *(*ascendingIterator);
    }

    // SideCrossIterator dereference operator
    int MagicalContainer::SideCrossIterator::operator*() const {
        if (sideCrossIterator == container.sideCrossOrder.end()) {
            throw out_of_range("Out of range");
        }
        return *(*sideCrossIterator);
    }

    // PrimeIterator dereference operator
    int MagicalContainer::PrimeIterator::operator*() const {
        if (primeIterator == container.primeOrder.end()) {
            throw out_of_range("Out of range");
        }
        return *(*primeIterator);
    }


    // Begin and end.

    // Set the iterator to the start of the ascendingOrder vector and index to 0.
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::begin() {
        ascendingIterator = container.ascendingOrder.begin();
        index = 0;
        return *this;
    }

    // Set the iterator to the end of the ascendingOrder vector and index to its size.
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::end() {
        ascendingIterator = container.ascendingOrder.end();
        index = container.ascendingOrder.size();
        return *this;
    }


    // Set the iterator to the start of the sideCrossOrder vector and index to 0.
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::begin() {
        sideCrossIterator = container.sideCrossOrder.begin();
        index = 0;
        return *this;
    }

    // Set the iterator to the end of the sideCrossOrder vector and index to its size.
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::end() {
        sideCrossIterator = container.sideCrossOrder.end();
        index = container.sideCrossOrder.size();
        return *this;
    }


    // Set the iterator to the start of the primeOrder vector and index to 0.
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::begin() {
        primeIterator = container.primeOrder.begin();
        index = 0;
        return *this;
    }

    // Set the iterator to the end of the primeOrder vector and index to its size.
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::end() {
        primeIterator = container.primeOrder.end();
        index = container.primeOrder.size();
        return *this;
    }

} //end of namespace ariel