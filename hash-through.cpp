#include <iostream>
#include <cstring>

int hash(const char * str) {
	return str[0];
}

class Hashtable {
private:
	struct Entry {
		const char * key;
		const char * value;
		bool deleted;

		Entry() : key(0), value(0), deleted(false) {}
	};

	int len;
	Entry * arr;
public:
	Hashtable() : len(7){
		arr = new Entry[len];
	}

	~Hashtable() {
		delete []arr;
	}

	void put(const char * key, const char * value) {
		del(key);

		int h = hash(key) % len;

		while (arr[h].key != 0)
			h = (h+3) % len;

		arr[h].key = key;
		arr[h].value = value;
		arr[h].deleted = false;
	}

	void del(const char * key) {
		int h = hash(key) % len;

		while (arr[h].key != 0 || arr[h].deleted) {
			if (arr[h].key != 0 && strcmp(arr[h].key, key) == 0) {
				arr[h].key = 0;
				arr[h].value = 0;
				arr[h].deleted = true;
			}

			h = (h+3) % len;
		}
	}

	const char * get(const char * key) {
		int h = hash(key) % len;

		while (arr[h].key != 0 || arr[h].deleted) {
			if (arr[h].key != 0 && strcmp(arr[h].key, key) == 0)
				return arr[h].value;

			h = (h+3) % len;
		}

		return 0;
	}
};

void main() {
	Hashtable table;

	table.put("aaa", "123");
	table.put("bbb", "345");
	table.put("abc", "567");
	table.del("aaa");
	table.put("cde", "789");
	table.put("bbb", "910");

	std::cout << (table.get("aaa") == 0) << std::endl;
	std::cout << table.get("bbb") << std::endl;
	std::cout << table.get("abc") << std::endl;
	std::cout << table.get("cde") << std::endl;
}
