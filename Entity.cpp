/*
 * Copyright (C) 2014 Eduardo Pinho (enet4mikeenet AT gmail.com)
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to
 * whom the Software is furnished to do so, subject to the
 * following conditions:
 *
 * The above copyright notice and this permission notice shall
 * be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
 * KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "Entity.h"

#include "MathUtils.h"
#include "Mat4x4f.h"
#include <stack>

#ifdef _GISELLE_DEBUG
#include <iostream>
#define D(x) std::cout << x
#else
#define D(x)
#endif

using namespace giselle;
using namespace scene;
using namespace math;

Entity::Entity(const Vector4f& pos, const Vector4f& ang,
				const std::list<Entity*>& children)
:	pos(pos)
,	ang(ang.x(), ang.y(), ang.z(), 0.0f)
,	parent(nullptr)
,	children()
{
	for (Entity* e : children)
	{
		if (e && e->parent == nullptr)
		{
			this->children.push_back(e);
			e->setParent(*this);
		}
	}
}

Entity::~Entity()
{
}

void Entity::setPosition(float x, float y, float z)
{
	this->pos = Vector4f(x, y, z, 1.0f);
}

void Entity::setOrientation(float pitch, float yaw, float roll)
{
	while (pitch >= 2*math::PI) pitch -= 2*math::PI;
	while (pitch < 0) pitch += 2*math::PI;
	while (yaw >= 2*math::PI) yaw -= 2*math::PI;
	while (yaw < 0) yaw += 2*math::PI;
	while (roll >= 2*math::PI) roll -= 2*math::PI;
	while (roll < 0) roll += 2*math::PI;

	this->ang = Vector4f(pitch, yaw, roll, 0.f);
}

void Entity::move(const Vector4f& mov)
{
	this->pos += {mov.x(), mov.y(), mov.z(), 0.f};
}

void Entity::rotate(const Vector4f& rot)
{
	this->rotate(rot.x(), rot.y(), rot.z());
}

void Entity::rotate(float d_pitch, float d_yaw, float d_roll)
{
	this->ang.x() += d_pitch;
	while(ang.x() < 0)
		ang.x() += 2*math::PI;
	while(ang.x() > 2*math::PI)
		ang.x() -= 2*math::PI;

	this->ang.y() += d_yaw;
	while(ang.y() < 0)
		ang.y() += 2*math::PI;
	while(ang.y() > 2*math::PI)
		ang.y() -= 2*math::PI;

	this->ang.z() += d_roll;
	while(ang.z() < 0)
		ang.z() += 2*math::PI;
	while(ang.z() > 2*math::PI)
		ang.z() -= 2*math::PI;
}

const Vector4f& Entity::position(void) const
{ return this->pos; }

const Vector4f& Entity::orientation(void) const
{ return this->ang; }

void Entity::absoluteVectors(Vector4f& pos, Vector4f& ang) const
{
	Vector4f r_ang = {0,0,0,0};
	Mat4x4f r_mat = Mat4x4f::IDENTITY;

	const Entity* p_ent;

	std::stack<const Entity*> ent_path;

	for (p_ent = this ; p_ent != nullptr ; p_ent = p_ent->getParent())
		ent_path.push(p_ent);

	while (!ent_path.empty())
	{
		p_ent = ent_path.top();
		r_ang += p_ent->orientation();
		math::translate(r_mat, p_ent->position());
		math::rotate(r_mat, p_ent->orientation());
		ent_path.pop();
	}

	r_mat.takeVector(pos);
	pos.normalize();
	ang = r_ang;
}

bool Entity::attach(Entity& ent)
{
	if (ent.getParent()) return false; // check for already defined

	//check for cycle
	for( const Entity* p_e = this ; p_e != nullptr ; p_e = p_e->getParent() )
		if (p_e==&ent) return false;

	this->children.push_back(&ent);
	ent.setParent(*this);

	return true;
}

void Entity::detach(Entity& ent)
{
	ent.setParent(nullptr);
	this->children.remove(&ent);
}

void Entity::render(Renderer& renderer) const
{
	//Nothing!
}

void Entity::setParent(Entity& parent_ent)
{
	this->parent = &parent_ent;
}

void Entity::setParent(std::nullptr_t)
{
	this->parent = nullptr;
}

const Entity* Entity::getParent(void) const
{
	return this->parent;
}

const std::list<Entity*>& Entity::getChildren(void) const
{
	return this->children;
}
