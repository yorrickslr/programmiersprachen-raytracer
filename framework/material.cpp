#include <material.hpp>


Material::Material() : 
    name_{"Material"},
    ka_{ Color{} },
    kd_{ Color{} },
    ks_{ Color{} },
    m_{ 0.0f } {}

Material::Material(std::string const& name, Color ka, Color kd, Color ks, float m) : 
    name_{ name },
    ka_{ ka },
    kd_{ kd },
    ks_{ ks },
    m_{ m } {}

Material::~Material(){}


std::string Material::get_name() const {
    return name_;
}

Color Material::get_ka() const {
    return ka_;
} 
Color Material::get_kd() const {
    return kd_;
}
Color Material::get_ks() const {
    return ks_;
}
float Material::get_m() const {
    return m_;
}

std::ostream& operator<<(std::ostream& os, Material const& m){
    os << "Name: " << m.get_name() << '\n' << "KA: " << m.get_ka() << '\n' << "KD: " << m.get_kd() << '\n' << "KS: " << m.get_ks() << '\n' << "M: " << m.get_m() << '\n';
    return os;
}
