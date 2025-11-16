//
// Created by aglorice on 2025/11/15.
//

#include <map>
#include <string>
#include <mutex>
#include <shared_mutex>

class dns_entry;

class dns_cache {
    std::map<std::string,dns_entry> entries;
    mutable std::shared_mutex entry_mutex;
    dns_entry find_entry(std::string const & domain) const {
        std::shared_lock<std::shared_mutex> lk(entry_mutex); // 这里相当于共享锁
        std::map<std::string,dns_entry>::const_iterator const it = entries.find(domain);
        return (it == entries.end()) ? dns_entry() : it->second;
    }

    void update_or_add_entry(std::string const & domain,dns_entry const &dn_details) {
        std::lock_guard<std::shared_mutex> lk(entry_mutex); // 这里相当于排他锁
        entries[domain] = dn_details;
    }

};

int main() {

}