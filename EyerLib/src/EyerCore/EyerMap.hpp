#ifndef	EYER_MAP_H
#define	EYER_MAP_H

#include <map>

namespace Eyer {

	template<typename K, typename V>
	class EyerMap
	{	
	public:
        EyerMap()
        {

        }

        ~EyerMap()
        {

        }

        int Insert(K & k, V & v)
        {
            m.insert(std::pair<K, V>(k, v));
            return 0;
        }

        int Size()
        {
            return m.size();
        }

        int Find(K & k, V & v)
        {
            typename std::map<K, V>::iterator it;
            it = m.find(k);
            if (it != m.end()){
                v = it->second;
                return 0;
            }

            return -1;
        }
	private:
        std::map<K, V> m;
	};

}

#endif