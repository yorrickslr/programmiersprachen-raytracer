#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP
#include <string>
#include <color.hpp>

class Material {
public:
	Material();
	Material(std::string const& name, Color ka, Color kd, Color ks, float m);
	~Material();

	std::string get_name() const;
	Color get_ka() const;
	Color get_kd() const;
	Color get_ks() const;
	float get_m() const;


private:
	std::string name_;
	Color ka_;
	Color kd_;
	Color ks_;
	float m_;
};

std::ostream& operator<<(std::ostream& os, Material const& m);

#endif
