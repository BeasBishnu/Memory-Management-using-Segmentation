#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TLB_SIZE 4
#define PAGE_SIZE 4096 // 4KB
#define MEMORY_SIZE 65536 // 64KB
#define VPN_MASK 0xFF00
#define OFFSET_MASK 0x00FF
#define SHIFT 8
// TLB entry structure
typedef struct {
    int VPN;    // Virtual Page Number
    int PFN;    // Physical Frame Number
    bool valid; // Valid bit
} TLBEntry;
TLBEntry tlb[TLB_SIZE];
int page_table[MEMORY_SIZE / PAGE_SIZE]; // Page table
// Function to initialize the TLB with some pre-made entries
void initialize_TLB() {
    tlb[0].VPN = 0x0A; tlb[0].PFN = 0x01; tlb[0].valid = true; // Example mapping
    tlb[1].VPN = 0x0B; tlb[1].PFN = 0x02; tlb[1].valid = true; // Example mapping
    tlb[2].VPN = 0x0C; tlb[2].PFN = 0x03; tlb[2].valid = true; // Example mapping
    tlb[3].VPN = 0x0D; tlb[3].PFN = 0x04; tlb[3].valid = true; // Example mapping
}
// Function to initialize the page table
void initialize_page_table() {
    for (int i = 0; i < MEMORY_SIZE / PAGE_SIZE; i++) {
        page_table[i] = i; // Map VPN to the same PFN for simplicity
    }
}
// Function to simulate a TLB lookup
bool TLB_Lookup(int VPN, int *PFN) {
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].VPN == VPN) {
            *PFN = tlb[i].PFN;
            return true; // TLB hit
        }
    }
    return false; // TLB miss
}
// Function to insert an entry into the TLB
void TLB_Insert(int VPN, int PFN) {
    //using FIFO while re4placing
    static int index = 0; 
    tlb[index].VPN = VPN;
    tlb[index].PFN = PFN;
    tlb[index].valid = true;
    index = (index + 1) % TLB_SIZE; // Wrap around to the beginning if TLB is full
}
int main() {
    int logical_address;
    initialize_TLB();
    initialize_page_table();
    while (1) {
        printf("Enter a 16-bit logical address in hex or -1 to exit: ");
        scanf("%x", &logical_address);

        if (logical_address == -1) {
            printf("Exiting...\n");
            break;
        }
        // Extract the vpn and Offset
        int VPN = (logical_address & VPN_MASK) >> SHIFT; // pseudocode line 1
        int offset = logical_address & OFFSET_MASK;      // pseudocode line 5
        int PFN;
        // TLB Lookup
        bool tlb_hit = TLB_Lookup(VPN, &PFN); // pseudocode line 2
        if (tlb_hit) {
            // TLB hit case
            printf("TLB Hit. Physical Address: 0x%x\n", (PFN << SHIFT) | offset); // pseudocode lines 3-7
        } else {
            // TLB miss case
            printf("TLB Miss. Page loaded into TLB.\n");
            // Fetch the PFN from the page table (simulated)
            PFN = page_table[VPN]; // pseudocode lines 10-12
            // Insert the new translation into the TLB
            TLB_Insert(VPN, PFN); // pseudocode line 18
            // Retry the instruction- just calculating physical address again
            printf("Retrying instruction... Physical Address: 0x%x\n", (PFN << SHIFT) | offset); // pseudocode line 19
        }
    }

    return 0;
}
