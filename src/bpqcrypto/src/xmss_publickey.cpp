/*
 * XMSS Public Key
 * An XMSS: Extended Hash-Based Siganture public key.
 * The XMSS public key does not support the X509 standard. Instead the
 * raw format described in [1] is used.
 *
 *   [1] XMSS: Extended Hash-Based Signatures,
 *       draft-itrf-cfrg-xmss-hash-based-signatures-06
 *       Release: July 2016.
 *       https://datatracker.ietf.org/doc/
 *       draft-irtf-cfrg-xmss-hash-based-signatures/?include_text=1
 *
 * (C) 2016,2017 Psi Crypto
 *
 * Botan is released under the Simplified BSD License (see license.txt)
 **/

#include "xmss_verification_operation.h"
#include "xmss_publickey.h"

namespace psicrypto {

	using Botan::Integrity_Failure;

XMSS_PublicKey::XMSS_PublicKey(const std::vector<uint8_t>& raw_key)
	: m_xmss_params(XMSS_PublicKey::deserialize_xmss_oid(raw_key))
	, m_wots_params(m_xmss_params.ots_oid())
{
	if(raw_key.size() < size())
	{
		throw Integrity_Failure("Invalid XMSS public key size detected.");
	}

	// extract & copy root from raw key.
	m_root.clear();
	m_root.reserve(m_xmss_params.element_size());
	auto begin = raw_key.begin() + 1 + sizeof(uint32_t);
	auto end = begin + m_xmss_params.element_size();
	std::copy(begin, end, std::back_inserter(m_root));

	// extract & copy public seed from raw key.
	begin = end;
	end = begin + m_xmss_params.element_size();
	m_public_seed.clear();
	m_public_seed.reserve(m_xmss_params.element_size());
	std::copy(begin, end, std::back_inserter(m_public_seed));
}

XMSS_Parameters::xmss_algorithm_t
XMSS_PublicKey::deserialize_xmss_oid(const std::vector<uint8_t>& raw_key)
{
	if(raw_key.size() < 5 || raw_key[0] != BPQ_XMSS_PREFIX)
	{
		throw Integrity_Failure("XMSS signature OID missing.");
	}

	// extract and convert algorithm id to enum type
	uint32_t raw_id = 0;
	for(size_t i = 1; i < 5; i++)
		{ raw_id = ((raw_id << 8) | raw_key[i]); }

	return static_cast<XMSS_Parameters::xmss_algorithm_t>(raw_id);
}

bool XMSS_PublicKey::verify(secure_vector<uint8_t> const & msg, secure_vector<uint8_t> const & signature)
{
	//XMSS_Signature sig(m_xmss_params.oid(), signature);
	XMSS_Verification_Operation op(*this);
	op.update(msg.data(), msg.size());
	return op.is_valid_signature(signature.data(), signature.size() );
}

std::vector<uint8_t> XMSS_PublicKey::raw_public_key() const
{
	std::vector<uint8_t> result
	{
		BPQ_XMSS_PREFIX,
		static_cast<uint8_t>(m_xmss_params.oid() >> 24),
		static_cast<uint8_t>(m_xmss_params.oid() >> 16),
		static_cast<uint8_t>(m_xmss_params.oid() >>  8),
		static_cast<uint8_t>(m_xmss_params.oid())
	};

	std::copy(m_root.begin(), m_root.end(), std::back_inserter(result));
	std::copy(m_public_seed.begin(),
				m_public_seed.end(),
				std::back_inserter(result));

	return result;
}

} // namespace psicrypto
