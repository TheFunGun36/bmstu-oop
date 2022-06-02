#pragma once
#include "jvector3d.h"
#include "jangle.h"
#include "property.h"
#include <string>
#include <list>

namespace Jora {

class SceneObject : public Printable {
public:
    using SelfPtr = std::shared_ptr<SceneObject>;
    using Self = SceneObject;

    inline SceneObject(const std::string& _label)
        : Visible(this, &Self::visible, &Self::setVisible)
        , Label(this, &Self::label, &Self::setLabel)
        , Type(this, &Self::type)
        , _visible(false)
        , _label(_label) { }
    inline virtual ~SceneObject() = default;

    Property<Self, bool> Visible;
    Property<Self, std::string> Label;
    Property<Self, std::type_info, PropReadOnly> Type;

    inline virtual const bool& visible() const { return _visible; }
    inline virtual void setVisible(const bool& _visible) {}

    inline virtual const std::string& label() const { return _label; }
    inline virtual void setLabel(const std::string& label) { _label = label; }

    inline virtual const std::type_info& type() const { return typeid(*this); }

    // COMPOSITE PART
    using Iterator = std::list<SelfPtr>::iterator;
    using IteratorConst = std::list<SelfPtr>::const_iterator;

    inline virtual bool isComposite() const { return false; }

    inline virtual bool add(const SelfPtr& sceneObject) { return false; }
    inline virtual bool remove(IteratorConst it) { return false; }
    inline virtual int count() { return 1; }
    inline virtual Iterator begin() { return Iterator(); }
    inline virtual Iterator end() { return Iterator(); }
    inline virtual IteratorConst begin() const { return IteratorConst(); }
    inline virtual IteratorConst end() const { return IteratorConst(); }
    inline virtual IteratorConst cbegin() const { return IteratorConst(); }
    inline virtual IteratorConst cend() const { return IteratorConst(); }

private:
    bool _visible;
    std::string _label;
};

}