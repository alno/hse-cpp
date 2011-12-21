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
		Entry * next;
	};

	int len;
	Entry ** arr;
public:
	Hashtable() : len(10){
		arr = new Entry*[len];
		memset(arr, 0, sizeof(Entry*) * len);
	}

	~Hashtable() {
		for (int i = 0; i < len; ++ i) {
			if (arr[i]) {
				Entry * e = arr[i];

				while (e) {
					Entry * next = e->next;
					delete e;
					e = next;
				}
			}
		}
	}

	void put(const char * key, const char * value) {
		del(key);

		int h = hash(key) % len;

		Entry * next = arr[h];

		arr[h] = new Entry();
		arr[h]->key = key;
		arr[h]->value = value;
		arr[h]->next = next;
	}

	void del(const char * key) {
		int h = hash(key) % len;

		if (arr[h] == 0)
			return;

		if (strcmp(arr[h]->key, key) == 0) {
			Entry * e = arr[h];
			arr[h] = e->next;
			delete e;
			return;
		}

		Entry * prev = arr[h];
		Entry * cur = arr[h]->next;

		while (cur) {
			if (strcmp(cur->key, key) == 0) {
				prev->next = cur->next;
				delete cur;
				return;
			}

			prev = cur;
			cur = cur->next;
		}
	}

	const char * get(const char * key) {
		int h = hash(key) % len;

		Entry * cur = arr[h];

		while (cur) {
			if (strcmp(cur->key, key) == 0)
				return cur->value;

			cur = cur->next;
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
