#define IA 16807
#define IM 2147483647
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define MAX_RANDOM_RANGE 0x7FFFFFFFUL

#define AM (1.0/IM)
#define EPS 1.2e-7
#define RNMX (1.0-EPS) 

class C_Random
{
private:
	int        m_idum;
	int        m_iy;
	int        m_iv[NTAB];
	int        GenerateRandomNumber(void);

public:
	void    SetSeed(int iSeed);
	float    RandomFloat(float flMinVal = 0.0f, float flMaxVal = 1.0f);
};

extern C_Random*Random;

class CNoSpread
{
public:
	void CalcClient(Vector vSpreadVec, Vector ViewIn, Vector &ViewOut);
	void CalcServer(Vector vSpreadVec, Vector ViewIn, Vector &vecSpreadDir);
	void GetSpreadVec(CUserCmd*cmd, Vector &vSpreadVec);
	void CompensateInAccuracyNumeric(CUserCmd*cmd);
	void RollSpread(CBaseCombatWeapon*localWeap, int seed, CUserCmd*cmd, Vector& pflInAngles);
	Vector& PredictPunchAngles()
	{
		IClientEntity* localPlayer = hackManager.pLocal();
		return (localPlayer->localPlayerExclusive()->GetAimPunchAngle() * 2.0f);
	}
private:
	void AngleVectors(Vector angles, Vector &f);
	void AngleVectors(const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
	void VectorAngles(const float *forward, float *angles);
	void VectorAngles(const Vector &forward, const Vector &pseudoup, Vector &angles);
};

extern CNoSpread NoSpread;