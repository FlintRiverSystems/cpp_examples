
/* Note: this file must be saved as UTF-8 WITHOUT signature for the utf8 string literal to work correctly */


using namespace std;
using namespace fmt;

template<class T>
std::string to_hex_string(const T& input)
{
	stringstream ss;

	auto bytes = reinterpret_cast<const unsigned char*>(input.data());
	auto n = input.size() * sizeof(typename T::value_type);

	string sep;
	for (auto i=0u; i<n; ++i)
	{
		ss << sep << format("{:02x}", *(bytes+i));
		if (sep.empty()) sep = " ";
	}

	return ss.str();
}

int main (int argc, char** argv)
{
	const string utf8 = "мдTт";
	const auto utf8_golden = "d0 bc d0 b4 54 d1 82";
	const auto utf16be_golden = "04 3c 04 34 00 54 04 42";
	const auto utf16le_golden = "3c 04 34 04 54 00 42 04";

	/**********************************************************************
	 * using code_cvt
	 *********************************************************************/

	{
		/* Note: codecvt is deprecated in C++17 and removed in C++26 */

		cout << "***********************" << endl;
		cout << "Using std::codecvt" << endl;
		cout << "***********************" << endl;
		cout << endl;

		cout << "utf8 string: " << utf8 << endl;

		cout << "utf8 size=" << utf8.size() << " BYTES, not characters";
		if (utf8.size() != 7) cout << " (should be 7)";
		cout << endl;

		auto utf8_hex = to_hex_string(utf8);
		cout << "utf8 bytes  : " << utf8_hex;

		if (utf8_hex == utf8_golden)
		{
			cout << " (correct)" << endl;
		}
		else
		{
			cout << endl;
			cout << "                     != " << endl;
			cout << "utf8 golden : " << utf8_golden << endl;
		}

		cout << endl;

		/* convert to UTF-16LE and check */

		wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converter;
		/* ony need 1 type of converter to go in both directions */

		auto utf16le = converter.from_bytes(utf8);

		cout << "converting to utf16le: " << endl;
		wcout << "utf16le string: " << utf16le << endl;
		cout << endl;

		if (sizeof(wchar_t) != 2)
			cout << "warning: codecvt to utf16 bytes does not work correctly for sizeof(wchar_t) != 2" << endl;

		cout << "utf16le size=" << utf16le.size() << " CHARACTERS, not bytes ";
		if (utf16le.size() != 4)
			cout << " (should be 4)";
		cout << endl;

		auto utf16le_hex = to_hex_string(utf16le);
		cout << "utf16le bytes : " << utf16le_hex;

		if (utf16le_hex == utf16le_golden)
		{
			cout << " (correct)" << endl;
		}
		else
		{
			cout << endl;
			cout << "                     != " << endl;
			cout << "utf16le golden: " << utf16le_golden << endl;
		}

		/* convert back to UTF-8 and check */

		cout << endl << "converting back to utf8: " << endl;

		auto utf8_2 = converter.to_bytes(utf16le);

		auto utf8_2_hex = to_hex_string(utf8_2);
		cout << "utf8 bytes  : " << utf8_2_hex;

		if (utf8_2_hex == utf8_golden)
		{
			cout << " (correct)" << endl;
		}
		else
		{
			cout << endl;
			cout << "                     != " << endl;
			cout << "utf8 golden : " << utf8_golden << endl;
		}

		/* there does not appear to be a way to generate UTF-16BE with code_cvt...*/
	}

	/**********************************************************************
	 * using boost::locale
	 *********************************************************************/

	{
		cout << endl;
		cout << "***********************" << endl;
		cout << "Using boost::locale" << endl;
		cout << "***********************" << endl;
		cout << endl;

		auto utf16le = boost::locale::conv::utf_to_utf<char16_t,char>(utf8);

		auto utf16le_hex = to_hex_string(utf16le);
		cout << "utf16le bytes : " << utf16le_hex;

		if (utf16le_hex == utf16le_golden)
		{
			cout << " (correct)" << endl;
		}
		else
		{
			cout << endl;
			cout << "                     != " << endl;
			cout << "utf16le golden: " << utf16le_golden << endl;
		}

		/* convert back to UTF-8 and check */

		cout << endl << "converting back to utf8: " << endl;

		auto utf8_2 = boost::locale::conv::utf_to_utf<char,char16_t>(utf16le);

		auto utf8_2_hex = to_hex_string(utf8_2);
		cout << "utf8 bytes  : " << utf8_2_hex;

		if (utf8_2_hex == utf8_golden)
		{
			cout << " (correct)" << endl;
		}
		else
		{
			cout << endl;
			cout << "                     != " << endl;
			cout << "utf8 golden : " << utf8_golden << endl;
		}

		/* there also does not appear to be a way to generate UTF-16BE with boost::locale... */

	}

	cout << endl;

	return 0;
}


