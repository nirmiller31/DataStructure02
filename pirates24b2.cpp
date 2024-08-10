#include "pirates24b2.h"
#include "unionFind.h"

oceans_t::oceans_t()
{
	// TODO: Your code goes here
}

oceans_t::~oceans_t()
{
	// TODO: Your code goes here
}


StatusType oceans_t::add_fleet(int fleetId)
{
	if(fleetId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(m_fleet_find.check_if_excist(fleetId)){
		return StatusType::FAILURE;
	}
	Fleet* new_fleet = new Fleet(fleetId);
	
	m_fleet_find.make_set(new_fleet);
	
	return StatusType::SUCCESS;
}


StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{

	if(fleetId <= 0 || pirateId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!m_fleet_find.check_identifier_fleet(fleetId) || m_pirate_table.search(pirateId)){
		return StatusType::FAILURE;
	}
;
	int fleet_pirate_rank = m_fleet_find.get_pirate_amount_and_increase(fleetId,1);

	Pirate* pirate_to_add = new Pirate(pirateId, fleetId, fleet_pirate_rank);

	m_pirate_table.insert(pirate_to_add);

	return StatusType::SUCCESS;
}


StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	// m_fleet_find.print();

	if(salary <= 0 || pirateId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!m_pirate_table.search(pirateId)){
		return StatusType::FAILURE;
	}
	Pirate* pirate_to_update = m_pirate_table.get(pirateId);
	pirate_to_update -> update_treasure(salary);

	return StatusType::SUCCESS;
}


output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{

	// std::cout << "im adding :" << fleetId << std::endl;
	// m_fleet_find.print();;

	if(fleetId <= 0){
		return output_t<int>(StatusType::INVALID_INPUT);
	}
	if(!m_fleet_find.check_identifier_fleet(fleetId)){
		return output_t<int>(StatusType::FAILURE);
	}
	int fleet_size = m_fleet_find.get_fleet_size(fleetId);

    return output_t<int>(fleet_size);
}


output_t<int> oceans_t::get_pirate_money(int pirateId)
{
	if(pirateId <= 0){
		return StatusType::INVALID_INPUT;
	}
	if(!m_pirate_table.search(pirateId)){
		return StatusType::FAILURE;
	}
	Pirate* pirate_to_know = m_pirate_table.get(pirateId);

    return output_t<int>(pirate_to_know -> get_treasure());
}


StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{

	// std::cout << "im argue:" << fleetId1 << " " << fleetId2 << std::endl;
	// m_fleet_find.print();

	if(fleetId1 <= 0 || fleetId2 <= 0 || fleetId1 == fleetId2){
		return StatusType::INVALID_INPUT;
	}
	if(!m_fleet_find.check_identifier_fleet(fleetId1) || !m_fleet_find.check_identifier_fleet(fleetId2)
		 ||
	(m_fleet_find.get_pirate_size(fleetId1) == 0) || (m_fleet_find.get_pirate_size(fleetId2) == 0)){
		return StatusType::FAILURE;
	}

	m_fleet_find.union_sets(m_fleet_find.find(fleetId1), m_fleet_find.find(fleetId2),fleetId1,fleetId2);
    return StatusType::SUCCESS;
}


StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{

	if(pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2){
		return StatusType::INVALID_INPUT;
	}
	// m_pirate_table.print();


	if(!m_pirate_table.search(pirateId1) || !m_pirate_table.search(pirateId2)
	|| (m_fleet_find.find_root(m_pirate_table.get(pirateId1)->get_fleet())) != (m_fleet_find.find_root(m_pirate_table.get(pirateId2)->get_fleet()))){
		return StatusType::FAILURE;
	}

	// m_fleet_find.print(); 
	// std::cout << "im argue:" << pirateId1 << " " << pirateId2 << std::endl;
	// m_pirate_table.print_pirates();
	// std::cout << "the identifier:" << pirateId1 << " " << pirateId2 << std::endl;
	// std::cout << "the first rank is:" << m_pirate_table.find_root(pirateId1) << "the second rank is:" << m_fleet_find.find_root(pirateId2) << std::endl;

	
	// std::cout << "the first : " << m_fleet_find.find_root(m_pirate_table.get(pirateId1)->get_fleet()) << "the second is:" << m_fleet_find.find_root(m_pirate_table.get(pirateId2)->get_fleet()) << std::endl;

	

	Pirate* pirate_1 = m_pirate_table.get(pirateId1);
	Pirate* pirate_2 = m_pirate_table.get(pirateId2);

    int first_fleet = pirate_1->get_fleet();
	int second_fleet = pirate_2->get_fleet();

	int first_pirate_rank = m_fleet_find.get_rank(first_fleet) + pirate_1->get_rank();
	int second_pirate_rank = m_fleet_find.get_rank(second_fleet) + pirate_2->get_rank();

	// m_fleet_find.print();
	// 
	// std::cout << "the first rank is:" << first_pirate_rank << "the second rank is:" << second_pirate_rank << std::endl;

	pirate_1->update_treasure(second_pirate_rank - first_pirate_rank);
	pirate_2->update_treasure(first_pirate_rank - second_pirate_rank);

    return StatusType::SUCCESS;
}
