#include <material.hpp>


Material::Material() : 
    std::string name_{"Material"}
    Color ka_{ Color{} }
    Color kd_{ Color{} }
    Color ks_{ Color{} }
    float m_{ 0.0f } {}

Material::Material(std::string const& name Color ka Color kd Color ks float m) : 
    std::string name_{ name }
    Color ka_{ ka }
    Color kd_{ kd }
    Color ks_{ ks }
    float m_{ m } {}

Material::~Material(){}


std::string Material::get_name() const {
    return name_;
}

Color Material::get_ka() const {
    return ka;
} 
Color Material::get_kd() const {
    return kd;
}
Color Material::get_ks() const {
    return ks;
}
float Material::get_m() const {
    return m;
}

std::ostream& operator<<(std::ostream& os, Material const& m){
    os << "Name: " << m.get_name() << '\n' << "KA: " << m.get_ka() << '\n' << "KD: " << m.get_kd() << '\n' << "KS: " << m.get_ks() << '\n' << "M: " << m.get_m() << '\n';
    return os;
}
