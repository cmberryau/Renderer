//
//  Transform.cpp
//  Renderer
//
//  Created by Christopher Berry on 17/09/2014.
//  Copyright (c) 2014 Christopher Berry. All rights reserved.
//

#include "Transform.hpp"

namespace Renderer
{
	Transform::Transform() : _position(0.0f, 0.0f, 0.0f),
							 _rotation(0.0f, 0.0f, 0.0f),
							 _scale(1.0f, 1.0f, 1.0f),
							 _composed_matrix(Matrix4f::Identity()),
							 _normal_matrix(Matrix4f::Identity())

	{

	}

	Transform::~Transform()
	{

	}

	void Transform::Translate(Vector3f & translation)
	{
		this->Translate(translation[0], translation[1], translation[2]);
	}

	void Transform::Translate(float x, float y, float z)
	{
		Matrix4f translation_matrix;

		_position[0] += x;
		_position[1] += y;
		_position[2] += z;

		translation_matrix = Matrix4f::Translate(x, y, z);

		_composed_matrix = _composed_matrix.Multiply(translation_matrix);
	}

	void Transform::SetPosition(Vector3f & position)
	{
		this->SetPosition(position[0], position[1], position[2]);
	}

	void Transform::SetPosition(float x, float y, float z)
	{
		Matrix4f translation_matrix = Matrix4f::Translate(-_position[0] + x,
														  -_position[1] + y,
														  -_position[2] + z);

		_composed_matrix = _composed_matrix.Multiply(translation_matrix);

		_position[0] = x;
		_position[1] = y;
		_position[2] = z;
	}

	void Transform::Rotate(Vector3f & rotation)
	{
		this->Rotate(rotation[0], rotation[1], rotation[2]);
	}

	void Transform::Rotate(float x, float y, float z)
	{
		Matrix4f rotation_matrix[3];

		_rotation[0] = x;
		_rotation[1] = y;
		_rotation[2] = z;

		for (int i = 0; i<3; i++)
		{
			Vector3f rotation_axes(0.0f);
			rotation_axes[i] = 1.0f;

			_rotation[i] = ClampRotation(_rotation[i]);

			rotation_matrix[i] = Matrix4f::Rotate(_rotation[i],
												  rotation_axes[0],
												  rotation_axes[1],
												  rotation_axes[2]);

			_normal_matrix = _normal_matrix.Multiply(rotation_matrix[i]);
			_composed_matrix = _composed_matrix.Multiply(rotation_matrix[i]);
		}
	}

	void Transform::SetRotation(Vector3f & rotation)
	{
		this->SetRotation(rotation[0], rotation[1], rotation[2]);
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		Matrix4f rotation_matrix[3];
		Vector3f rotation(x, y, z);

		for (int i = 0; i<3; i++)
		{
			Vector3f rotation_axes(0.0f);
			rotation_axes[i] = 1.0f;

			_rotation[i] = ClampRotation(_rotation[i]);

			rotation_matrix[i] = Matrix4f::Rotate(-_rotation[i] + rotation[i],
				rotation_axes[0],
				rotation_axes[1],
				rotation_axes[2]);

			_normal_matrix = _normal_matrix.Multiply(rotation_matrix[i]);
			_composed_matrix = _composed_matrix.Multiply(rotation_matrix[i]);
			_rotation[i] = rotation[i];
		}
	}

	double Transform::ClampRotation(double rotation)
	{
		double clamped = fmod(rotation, 360.0);

		if (clamped < 0)
			clamped += 360.0;

		return clamped;
	}

	float Transform::ClampRotation(float rotation)
	{
		float clamped = fmodf(rotation, 360.0);

		if (clamped < 0)
			clamped += 360.0;

		return clamped;
	}

	void Transform::Scale(Vector3f & scale)
	{
		this->Scale(scale[0], scale[1], scale[2]);
	}

	void Transform::Scale(float x, float y, float z)
	{
		Matrix4f scale_matrix;

		_scale[0] += x;
		_scale[1] += y;
		_scale[2] += z;

		_composed_matrix = _composed_matrix.Multiply(scale_matrix);
	}

	void Transform::SetScale(Vector3f & scale)
	{
		this->SetScale(scale[0], scale[1], scale[2]);
	}

	void Transform::SetScale(float x, float y, float z)
	{
		Matrix4f scale_matrix = Matrix4f::Scale(x, y, z);

		_scale[0] = x;
		_scale[1] = y;
		_scale[2] = z;

		_composed_matrix = _composed_matrix.Multiply(scale_matrix);
	}

	const Matrix4f & Transform::NormalMatrix() const
	{
		return _normal_matrix;
	}

	const Matrix4f & Transform::ComposedMatrix() const
	{
		return _composed_matrix;
	}
}