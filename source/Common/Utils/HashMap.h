#pragma once

#include <string>
#include <vector>

#include "Common/TaskPool/Utils/RWLock.h"

template <class T> struct MapEntry
{
    unsigned int Key;
    T Value;
};

template <class T> class HashMap
{
    public:
        typedef MapEntry<T> MapEntryType;
        typedef std::vector<MapEntryType> HashMapType;

    private:
        HashMapType m_TableEntries;
        CRWLock m_Lock;

    public:
        HashMap(void)
        {
            m_TableEntries.reserve(128);
        }

        ~HashMap(void)
        {
            m_TableEntries.clear();
        }

        HashMapType &GetHashMap(void)
        {
            return m_TableEntries;
        }

        unsigned int GetKeyHash(const std::string &key)
        {
            int hashKey = 0;

            for (unsigned int i = 0; i < key.size(); ++i)
            {
                hashKey += key[i];
            }

            return hashKey;
        }

        MapEntryType *find(const std::string &key)
        {
            unsigned int l_HashKey = GetKeyHash(key);

            m_Lock.ReadLock();
                for (unsigned int i = 0; i < m_TableEntries.size(); ++i)
                {
                    if (l_HashKey == m_TableEntries[i].Key)
                    {
                        m_Lock.ReadUnLock();
                        return &m_TableEntries[i];
                    }
                }
            m_Lock.ReadUnLock();

            return NULL;
        }

        MapEntryType *find(unsigned int hashKey)
        {
            m_Lock.ReadLock();
                for (unsigned int i = 0; i < m_TableEntries.size(); ++i)
                {
                    if (hashKey == m_TableEntries[i].Key)
                    {
                        m_Lock.ReadUnLock();
                        return &m_TableEntries[i];
                    }
                }
            m_Lock.ReadUnLock();

            return NULL;
        }

        void Remove(const std::string &key)
        {
            unsigned int l_HashKey = getKeyHash(key);

            m_Lock.WriteLock();
                for (HashMapType::iterator it = m_TableEntries.begin(); it != m_TableEntries.end(); it++)
                {
                    if (it->Key == l_HashKey)
                    {
                        m_Lock.WriteUnLock();
                        m_TableEntries.erase(it);
                        return;
                    }
                }
            m_Lock.WriteUnLock();
        }

        bool Add(const std::string &key, const T &value, bool override = false)
        {
            unsigned int keyHash = GetKeyHash(key);
            MapEntry<T> *entryFound = find(keyHash);

            m_Lock.WriteLock();
                if (!override && entryFound != NULL)
                {
                    m_Lock.WriteUnLock();
                    return false;
                }

                if (entryFound != NULL)
                {
                    entryFound->Value = value;
                    m_Lock.WriteUnLock();
                    return true;
                }

                MapEntry<T> l_Entry = { keyHash, value };
                m_TableEntries.push_back(l_Entry);
            m_Lock.WriteUnLock();

            return true;
        }
};
