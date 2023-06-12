#ifndef CPP_MAGICALCONTAINER_HPP
#define CPP_MAGICALCONTAINER_HPP

#include <vector>
#include <algorithm>

namespace ariel {

    class MagicalContainer{
    private:
        std::vector<int> mainElements;
        std::vector<int*> ascendingOrder;
        std::vector<int*> sideCrossOrder;
        std::vector<int*> primeOrder;

    public:
        MagicalContainer() = default;
        ~MagicalContainer() = default;
        MagicalContainer(const MagicalContainer& other) = default;
        MagicalContainer& operator=(const MagicalContainer& other) = default;
        MagicalContainer(MagicalContainer&& other) = default;
        MagicalContainer& operator=(MagicalContainer&& other) = default;

        void addElement(int element);
        void removeElement(int element);
        int size() const;

        std::vector<int> getElements() const;

        void addToAscendingOrder();
        void addToSideCrossOrder();
        void addToPrimeOrder();



        class AscendingIterator {
        private:
            MagicalContainer& container;
            std::vector<int*>::iterator ascendingIterator;
            size_t index;

        public:
            AscendingIterator(MagicalContainer& cont);
            AscendingIterator(const AscendingIterator& other);
            AscendingIterator(AscendingIterator&& other) = default;
            ~AscendingIterator() = default;


            bool operator==(const AscendingIterator& other) const;
            bool operator!=(const AscendingIterator& other) const;
            bool operator>(const AscendingIterator& other) const;
            bool operator<(const AscendingIterator& other) const;
            AscendingIterator& operator++();
            AscendingIterator& operator=(const AscendingIterator& other);
            int operator*() const;

            AscendingIterator& begin();
            AscendingIterator& end();
            AscendingIterator& operator=(AscendingIterator&& other) = delete;
        };

        class SideCrossIterator {
        private:
            MagicalContainer& container;
            std::vector<int*>::iterator sideCrossIterator;
            size_t index;

        public:
            SideCrossIterator(MagicalContainer& cont);
            SideCrossIterator(const SideCrossIterator& other);
            SideCrossIterator(SideCrossIterator&& other) = default;
            ~SideCrossIterator() = default;

            bool operator==(const SideCrossIterator& other) const;
            bool operator!=(const SideCrossIterator& other) const;
            bool operator>(const SideCrossIterator& other) const;
            bool operator<(const SideCrossIterator& other) const;
            SideCrossIterator& operator++();
            SideCrossIterator& operator=(const SideCrossIterator& other);
            int operator*() const;

            SideCrossIterator& begin();
            SideCrossIterator& end();
            SideCrossIterator& operator=(SideCrossIterator&& other) = delete;
        };

        class PrimeIterator {
        private:
            MagicalContainer& container;
            std::vector<int*>::iterator primeIterator;
            size_t index;

        public:
            PrimeIterator(MagicalContainer& cont);
            PrimeIterator(const PrimeIterator& other);
            PrimeIterator(PrimeIterator&& other) = default;
            ~PrimeIterator() = default;

            bool operator==(const PrimeIterator& other) const;
            bool operator!=(const PrimeIterator& other) const;
            bool operator>(const PrimeIterator& other) const;
            bool operator<(const PrimeIterator& other) const;
            PrimeIterator& operator++();
            PrimeIterator& operator=(const PrimeIterator& other);
            int operator*() const;

            PrimeIterator& begin();
            PrimeIterator& end();
            PrimeIterator& operator=(PrimeIterator&& other) = delete;
        };
    };

}

#endif
