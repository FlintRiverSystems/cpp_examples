
/* Note: this file must be saved as UTF-8 WITHOUT signature for the utf8 string literal to work correctly */


using namespace std;
using namespace fmt;

std::string to_hex_string(const std::string& input)
{
	stringstream ss;

	string sep;
	for (auto i : input)
	{
		ss << sep << format("{:02x}", static_cast<unsigned char>(i));
		if (sep.empty()) sep = " ";
	}

	return ss.str();
}

std::string to_hex_string(const std::wstring& input)
{
	stringstream ss;

	string sep;
	for (auto i : input)
	{
		ss << sep << format("{:02x}", i >> 8);
		if (sep.empty()) sep = " ";
		ss << sep << format("{:02x}", i & 0xFF);
	}

	return ss.str();
}

int main (int argc, char** argv)
{
	const string utf8 = "мдTт";
	const auto utf8_golden = "d0 bc d0 b4 54 d1 82";
	const auto utf16_golden = "04 3c 04 34 00 54 04 42";

	cout << "utf8 string: " << utf8 << endl;

	cout << "utf8 size=" << utf8.size() << " BYTES, not characters";
	if (utf8.size() != 7) cout << " (should be 7)";
	cout << endl;

	auto utf8_hex = to_hex_string(utf8);
	cout << "utf8 bytes  : " << utf8_hex << endl;

	if (utf8_hex != utf8_golden)
		cout << "utf8 golden : " << utf8_golden << endl;

	/* convert to UTF-16 and check */

	wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
		/* ony need 1 type of converter to go in both directions */


	auto utf16 = converter.from_bytes(utf8);

	wcout << "utf16 string: " << utf16 << endl;
	cout << endl;

	cout << "utf16 size=" << utf16.size() << " CHARACTERS, not bytes ";
	if (utf16.size() != 4)
		cout << " (should be 4)";
	cout << endl;

	auto utf16_hex = to_hex_string(utf16);
	cout << "utf16 bytes : " << utf16_hex << endl;

	if (utf16_hex != utf16_golden)
		cout << "utf16 golden: " << utf16_golden << endl;

	/* convert back to UTF-8 and check */

	auto utf8_2 = converter.to_bytes(utf16);

	auto utf8_2_hex = to_hex_string(utf8_2);
	cout << "utf8 bytes  : " << utf8_2_hex << endl;

	if (utf8_2_hex != utf8_golden)
		cout << "utf8 golden : " << utf8_golden << endl;

	return 0;
}


