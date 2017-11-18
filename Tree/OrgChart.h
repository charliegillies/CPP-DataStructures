#ifndef ORGCHART_H
#define ORGCHART_H

#include <iostream>
#include <string>
#include <vector>

// Forward declarations.
class Person;
class OrgChart;

/** A person within the organisation. */
class Person {
	// OrgChart is allowed to use the private members of Person.
	friend class OrgChart;

public:
	/** Constructor, specifying the person's name and manager. */
	Person(const std::string& name, Person *parent)
		: name_(name), parent_(parent) {
	}

	/** Destructor. */
	~Person() {
		for (Person *child : children_) {
			delete child;
		}
	}

	/** Create and return a new Person object, making it a child of this one. */
	Person *add_child(const std::string& name) {
		Person *child = new Person(name, this);
		children_.push_back(child);
		return child;
	}

	/** Return the level of this person within the organisation.
	    The CEO is level 1; they manage people at level 2, and so on. */
	// "const" here (and below) means that this method doesn't change this object.
	int level() const {
		if (parent_ == nullptr) {
			return 1;
		}
		else
			return parent_->level() + 1;
	}

	bool contains(const std::string& name) const {
		// if me.. true
		if (name_ == name) 
			return true;

		// if any of the children, true
		for (auto child : children_) {
			if (child->contains(name)) {
				return true;
			}
		}

		// otherwise, no.
		return false;
	}

	int size() {
		// start count at child size
		int count = children_.size();

		for (auto child : children_) {
			// then increase by childs own children size
			count += child->size();
		}

		// return +1 if root
		return (parent_ != nullptr) ? count : count + 1;
	}

	int height(int depth = 1) {
		if(children_.size() == 0) return depth;
		
		// self
		int height = 1;
		
		// find the longest branch..
		for (auto child : children_) {
			int h = child->height();
			
			if (h > height) {
				height = h;
			}
		}

		return depth + height;
	}
	
private:
	// -- Helper methods that will be used by OrgChart below --

	/** Print out this person and all their descendants, indented by depth spaces. */
	void print(int depth = 0) const {
		for (int i = 0; i < depth; i++) {
			std::cout << " ";
		}
		std::cout << "- " << name_ << "\n";

		// Print the children, indented by one more space.
		for (Person *child : children_) {
			child->print(depth + 1);
		}
	}

	// FIXME: Add more helper methods here!

	// -- Member variables --

	/** The name of this person. */
	std::string name_;

	/** Pointer to this person's manager.
		If this person is at the root of the tree, parent_ == nullptr. */
	Person *parent_;

	/** Pointers to the people this person manages.
	    Each Person owns the people they manage, so it's responsible for
		deleting them in the destructor above. */
	std::vector<Person *> children_;
};

/** A organisational chart, represented as a tree of Person nodes. */
class OrgChart {
public:
	/** Constructor, specifying the CEO's name. */
	OrgChart(const std::string& name)
		: root_(new Person(name, nullptr)) {
	}

	/** Destructor. */
	~OrgChart() {
		delete root_;
	}

	/** Return a pointer to the CEO's Person object. */
	Person *root() {
		return root_;
	}

	/** Print out all the people in the organisation. */
	void print() const {
		root_->print();
	}

	/** Returns true if name is a member of the organisation. */
	bool contains(const std::string& name) const {
		return root_->contains(name);
	}

	/** Returns the number of people in the organisation. */
	int size() const {
		return root_->size();
	}

	/** Returns the number of levels in the org chart. */
	int height() const {
		return root_->height();
	}

private:
	/** Pointer to the Person at the root of the tree.
		This is guaranteed not to be nullptr, i.e. there's always at
		least one person in the organisation.
		The OrgChart object owns this Person, and is responsible
		for deleting it in the destructor above. */
	Person *root_;
};

#endif