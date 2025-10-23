#include <livecmd/alert.h>
#include <iostream>


namespace alert {
	namespace db {
		void _prefix() {
			print(L"[DATABASE]", L"bright_cyan", L"bold");
		}
		void close() {
			_prefix();
			print(L" -> Encrypted and safely closed", L"white", L"reset");
			std::cout << std::endl;
		}
		void notfound() {
			_prefix();
			print(L" -> No Database Found", L"red", L"reset");
			print(L" -> Creating primary...", L"white", L"reset");
			std::wcout << std::endl;
			std::wcout << std::endl;
		}
		void found() {
			_prefix();
			print(L" -> Selected primary database", L"white", L"reset");
			std::wcout << std::endl;
		}
		void not_open() {
			_prefix();
			print(L" -> cannot open db/primary.nightlock1", L"white", L"reset");
			std::wcout << std::endl;
		}
		void readmaster() {
			_prefix();
			print(L" -> Enter master-password > ", L"white", L"reset");
		}
		void createmaster() {
			_prefix();
			print(L" -> Create master-password > ", L"white", L"reset");
		}
		void incorrectmaster() {
			_prefix();
			print(L" -> Master-password is invalid", L"red", L"reset");
			std::wcout << std::endl;
		}
		void save() {
			_prefix();
			print(L" -> Encrypted and saved", L"white", L"reset");
			std::wcout << std::endl;
		}
		void load() {
			_prefix();
			print(L" -> Decrypted and loaded", L"white", L"reset");
			std::wcout << std::endl;
		}
	}
}