#ifndef _ST_H_
#define _ST_H_

template<class ST>
class _KeyIterator{
    public:
        typedef _KeyIterator<ST> self;
        typedef typename ST::key_t key_t; 
        _KeyIterator();
        virtual ~_KeyIterator();
        virtual key_t& operator* () const = 0;
        virtual self& operator ++();//prefix increment only
        virtual bool operator == (const self& other) const = 0;
        virtual bool operator != (const self& other) const = 0;
};


template<class Key, class Value>
class SearchTable{
    public:
        typedef SearchTable<Key, Value> self;
        typedef _KeyIterator<self> iterator;
        typedef Key key_t;
        typedef Value value_t;

        SearchTable();
        virtual ~SearchTable();
        virtual Value get(const Key& key) = 0;
        virtual void put(const Key& key, const Value& value) = 0;
        virtual void del(const Key& key) = 0;
        virtual iterator keys() = 0;
};

#endif
