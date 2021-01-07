#ifndef STORAGE_H
#define STORAGE_H


#include <boost/noncopyable.hpp>

#include <vector>
#include <unordered_map>
#include <string>


struct Data
{
public:
	explicit Data()
	{}

	explicit Data(std::string value, std::string timestamp) :
		m_value(value),
		m_timestamp(timestamp)
	{}

	std::string getValue() const
	{
		return m_value;
	}

	std::string getTimestamp() const
	{
		return m_timestamp;
	}


private:
	std::string m_value;
	std::string m_timestamp;

};

class Storage : boost::noncopyable
{
public:
	void add(std::string name, Data& d)
	{
		m_storage[name].emplace_back(d);
	}

	std::string toJsonFormat(const std::string& name, std::vector<Data>& d)
	{
		std::string result = name + " {\n\r";

		for (int i = 0; i < d.size(); ++i)
		{
			result += "\tvalue: [\n\r\t\t" + d[i].getValue() + "\n\r\t]\n\r";
			result += "\ttimestamp: [\n\r\t\t" + d[i].getTimestamp() + "\n\r\t]\n\r";
		}

		result += "}\n\r";

		return result;
	}

	std::string get(std::string name)
	{
		if (name == "*")
			return getAll();
		auto p = m_storage.find(name);
		if (p == m_storage.end())
			return "Error: This metric is not in storage\n\r";
		
		return toJsonFormat(name, p->second);
	}

	std::string getAll()
	{
		std::string result = "";
		for (auto& i : m_storage)
		{
			result += toJsonFormat(i.first, i.second);
		}

		return result;
	}

	static Storage& getInstance()
	{
		static Storage storage;
		return storage;
	}

private:
	std::unordered_map<std::string, std::vector<Data> > m_storage;
};

#endif