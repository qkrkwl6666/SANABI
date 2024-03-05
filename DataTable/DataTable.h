#pragma once
class DataTable
{

public:
	enum class Types
	{
		String,
	};
	static const int TotalTypes = 6;

private:
	Types type;
public:

	inline DataTable(Types t) :type(t) {};
	virtual ~DataTable() = default;
	DataTable(const DataTable&) = delete;
	DataTable(DataTable&&) = delete;
	DataTable& operator=(const DataTable&) = delete;
	DataTable& operator=(DataTable&&) = delete;

	virtual bool Load() = 0;
	virtual void Release() = 0;

};

