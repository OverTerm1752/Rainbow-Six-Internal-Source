#pragma once

struct ubiViewMatrix {
	ubiViewMatrix() noexcept
		: m_data() {}

	float* operator[](int index) noexcept {
		return m_data[index];
	}

	const float* operator[](int index) const noexcept {
		return m_data[index];
	}

	float m_data[4][4];
};