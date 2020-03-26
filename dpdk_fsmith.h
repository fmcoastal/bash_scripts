#ifndef _dpdk_fsmith
#define _dpdk_fsmith

/*   output of dpdk-devbind -s for crb96xx   
0002:02:00.0 'Device a063' if=eth0 drv=octeontx2-nicpf unused=vfio-pci
0002:03:00.0 'Device a063' if=eth1 drv=octeontx2-nicpf unused=vfio-pci
0002:04:00.0 'Device a063' if=eth2 drv=octeontx2-nicpf unused=vfio-pci
0002:05:00.0 'Device a063' if=eth3 drv=octeontx2-nicpf unused=vfio-pci
0002:06:00.0 'Device a063' if=eth4 drv=octeontx2-nicpf unused=vfio-pci
0002:07:00.0 'Device a063' if=eth5 drv=octeontx2-nicpf unused=vfio-pci
0002:08:00.0 'Device a063' if=eth6 drv=octeontx2-nicpf unused=vfio-pci
0002:09:00.0 'Device a063' if=eth7 drv=octeontx2-nicpf unused=vfio-pci
  
        //fs_add_mac_address(int port_id)
//            | 7 | 5 | 3 |
//      |  0  | 6 | 4 | 2 | 1 |  |8|
//  dpdk-ddpdk-devbind
// eth 1  0002:03:00.0  cgx1.0
// eth 2  0002:04:00.0  cgx1.1   port_id 0
// eth 3  0002:04:00.0  cgx1.2
// eth 4  0002:06:00.0  cgx2.0   port_id 1
// eth 5  0002:07:00.0  cgx2.1   port_id 2
// eth 6  0002:08:00.0  cgx2.2
// eth 7  0002:09:00.0  cgx2.3
// -p 7
*/

#define WAI() printf("%d-%s:%s\n",__LINE__,__FILE__,__FUNCTION__)

#define INDENT_SIZE 3
#define INDENT(x) \
    char s[64]= {0};\
    int i;\
    for ( i = 0 ; i < (INDENT_SIZE * x) ; i++) s[i] = ' ';




// Great Reference:
//  https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences

//Output Manipulations
//static char C_BLACK[]   ={0x1b,'[','3','0','m',0x00};  //BLACK=$'\e[30m'
//static char C_RED[]     ={0x1b,'[','3','1','m',0x00};  // RED=$'\e[31m'
static char C_RED_BLACK[]     ={0x1b,'[','3','1',';','4','0','m',0x00};  // RED=$'\e[31m'  on black
static char C_GREEN[]   ={0x1b,'[','3','2','m',0x00};  // GREEN=$'\e[32m'
static char C_YELLOW[]  ={0x1b,'[','3','3','m',0x00};  // YELLOW=$'\e[33m'
//static char C_BLUE[]    ={0x1b,'[','3','4','m',0x00};  // BLUE=$'\e[34m'
//static char C_MAGENTA[] ={0x1b,'[','3','5','m',0x00};  // MAGENTA=$'\e[35m'
static char C_MAGENTA_BLACK[]     ={0x1b,'[','3','5',';','4','0','m',0x00};  // RED=$'\e[31m'  on black
static char C_CYAN[]    ={0x1b,'[','3','6','m',0x00};  // CYAN=$'\e[36m'
//static char C_GRAY[]    ={0x1b,'[','3','7','m',0x00};  // GRAY=$'\e[37m'
static char C_WHITE[]   ={0x1b,'[','0','m',0x00};     // WHITE=$'\e[0m'

//static char C_NORMAL[]   ={0x1b,'[','0','m',0x00};  // NORMAL=$'\e[0m'
//static char C_BOLD[]     ={0x1b,'[','1','m',0x00};  // BOLD=$'\e[1m'
//static char C_UNDERLINE[]={0x1b,'[','4','m',0x00};  // UNDERLINE=$'\e[4m'
//static char C_BLINK[]    ={0x1b,'[','5','m',0x00};  // BLINK=$'\e[5m'
//static char C_INVERT[]   ={0x1b,'[','7','m',0x00};  // INVERT=$'\e[7m'

static char * NextColor[] = { C_GREEN,C_YELLOW,C_RED_BLACK,C_CYAN,C_MAGENTA_BLACK ,NULL};
static int NextColorIndex = 0;

static char * GetNextColor(void)
    {
      NextColorIndex++;
      if(NextColor[ NextColorIndex] == NULL) NextColorIndex = 0 ;
      return NextColor[ NextColorIndex];
    }

#define  NEXT_COLOR() printf("%s",GetNextColor()); 
#define  WHITE() printf("%s",C_WHITE); 



/** Information for a given RSS type. */
 struct rss_type_info {
         const char *str; /**< Type name. */
         uint64_t rss_type; /**< Type value. */
 };


static const struct rss_type_info rss_type_table[] = {
        { "all", ETH_RSS_IP | ETH_RSS_TCP |
                        ETH_RSS_UDP | ETH_RSS_SCTP |
                        ETH_RSS_L2_PAYLOAD },
        { "none", 0 },
        { "ipv4", ETH_RSS_IPV4 },
        { "ipv4-frag", ETH_RSS_FRAG_IPV4 },
        { "ipv4-tcp", ETH_RSS_NONFRAG_IPV4_TCP },
        { "ipv4-udp", ETH_RSS_NONFRAG_IPV4_UDP },
        { "ipv4-sctp", ETH_RSS_NONFRAG_IPV4_SCTP },
        { "ipv4-other", ETH_RSS_NONFRAG_IPV4_OTHER },
        { "ipv6", ETH_RSS_IPV6 },
        { "ipv6-frag", ETH_RSS_FRAG_IPV6 },
        { "ipv6-tcp", ETH_RSS_NONFRAG_IPV6_TCP },
        { "ipv6-udp", ETH_RSS_NONFRAG_IPV6_UDP },
        { "ipv6-sctp", ETH_RSS_NONFRAG_IPV6_SCTP },
        { "ipv6-other", ETH_RSS_NONFRAG_IPV6_OTHER },
        { "l2-payload", ETH_RSS_L2_PAYLOAD },
        { "ipv6-ex", ETH_RSS_IPV6_EX },
        { "ipv6-tcp-ex", ETH_RSS_IPV6_TCP_EX },
        { "ipv6-udp-ex", ETH_RSS_IPV6_UDP_EX },
        { "port", ETH_RSS_PORT },
        { "vxlan", ETH_RSS_VXLAN },
        { "geneve", ETH_RSS_GENEVE },
        { "nvgre", ETH_RSS_NVGRE },
        { "ip", ETH_RSS_IP },
        { "udp", ETH_RSS_UDP },
        { "tcp", ETH_RSS_TCP },
        { "sctp", ETH_RSS_SCTP },
        { "tunnel", ETH_RSS_TUNNEL },
        { NULL, 0 },
};






/*  
 *   COnverts an IP address into a printable string
 */
static inline char * format_ip_addr(char * str,uint32_t ip);
static inline char * format_ip_addr(char * str,uint32_t ip)
{
   sprintf(str,"%d.%d.%d.%d",((ip >> 24)&0xff),((ip >> 16)&0xff),((ip >> 8)&0xff),((ip >> 0)&0xff));
   return str;
}

/*  
 *   converts a ethernet address into a printable String
 */
static inline char * format_mac_addr(char * str,struct rte_ether_addr *m );
static inline char * format_mac_addr(char * str,struct rte_ether_addr *m )
{
   sprintf(str,"%02x:%02x:%02x:%02x:%02x:%02x",m->addr_bytes[0]
                                              ,m->addr_bytes[1]
                                              ,m->addr_bytes[2]
                                              ,m->addr_bytes[3]
                                              ,m->addr_bytes[4]
                                              ,m->addr_bytes[5]);
   return str;
}

static inline void PrintMac(unsigned int portid, struct rte_ether_addr *m)
{
        printf("Port %u, MAC address: %02X:%02X:%02X:%02X:%02X:%02X\n\n",
                        (unsigned int) portid,
                        m->addr_bytes[0],
                        m->addr_bytes[1],
                        m->addr_bytes[2],
                        m->addr_bytes[3],
                        m->addr_bytes[4],
                        m->addr_bytes[5]);
}


#undef  PRINT_BUFF_SHORT

#ifdef PRINT_BUFF_SHORT
#define PrintBuff( x, y) PrintBuffShort(x,y)
#else
#define PrintBuff( x, y) PrintBuffLong(x,y,0)
#endif




/*  
 *  dumps a character buffer to the screen
 */
#ifdef PRINT_BUFF_SHORT
static inline void PrintBuffShort(uint8_t * ptr , int32_t sz);
static inline void PrintBuffShort(uint8_t * ptr , int32_t sz)
{
  int32_t index;

  for ( index = 0 ; index  < sz ; index++)
  {
    if( index%16 == 0) printf("\n%3d",index);
    if( index%8 == 0) printf("  ");
    printf("%02x ", *(ptr + index) );
  }
  printf("\n");
}


#else
#define LLU long long unsigned
#define fsprint printf

static inline void PrintBuffLong(uint8_t * buffer, int32_t bufferSize,uint8_t * Address)
{
    uint8_t * tmpptr0  = buffer; 
    uint8_t * tmpptr1  = tmpptr0; 
    int64_t  i          = 0 ;
    int64_t  m          = 0 ;
    int64_t  n          = 0 ;
    int64_t  j          = 0 ;
    int64_t  PrintCount = 0 ;   // used as counter to denote when to print \nadderss
    int64_t  BlankCnt   = 0 ;
   
    
    // align the lead
    BlankCnt = (unsigned long)Address & 0x000000000f;
    
    // print the lead
    if( BlankCnt != 0)  // if 0 jump to main body 
    {        
        for ( PrintCount = 0 ; PrintCount < BlankCnt ; PrintCount++ )
        {
            if( PrintCount == 0) // space between fields
            {
                fsprint("\n%016x",(unsigned)((unsigned long)Address & ~0x000000000f)); 
                tmpptr1 = tmpptr0;
            }
            if( (PrintCount % 8) == 0)
            {
                fsprint(" ");
            }    
            fsprint("   ");
        }
        PrintCount--;  // remove last increment of printcount
        // print PrintCount data
        for ( m = 0  ; (PrintCount < 0xf) && (i < bufferSize); i++, m++,PrintCount++)
        {
            if(PrintCount % 8 == 0)
            {
                fsprint(" ");
            }    
            fsprint(" %02x",(unsigned char)(*tmpptr0++));
            Address++;
        }
        
        // special case here when count is less than one line and not starting at zero
        if ( i == bufferSize) 
        {
            // print out the last space 
            for (      ; (PrintCount < 0x0f) ; PrintCount++ )
            {
                if( PrintCount  % 8 == 0)
                {
                    fsprint(" ");
                }    
                fsprint("   ");
            }
            // print PrintCount text space
            for ( PrintCount = 0 ; (PrintCount < BlankCnt) ; PrintCount++ )
            {
                if( PrintCount == 0)   // space between fields 
                {
                    fsprint(" ");
                }
                else if( PrintCount  % 8 == 0)
                {
                    fsprint(" ");
                }    
                fsprint(" ");
            }             
            // print PrintCount characters
            for( n = 0 ; (n < m) ; n++)
            {
                if( n == 0 ) printf(" ");
                if((*tmpptr1 >=0x20) && (*tmpptr1 <= 0x7e))
                    fsprint("%c",*tmpptr1);
                else
                    fsprint(".");
                tmpptr1++;
            }
            printf("\n");
            return;
        } // end i == bufferSize
        
        // print PrintCount text space
        for ( PrintCount = 0 ; (PrintCount < BlankCnt) ; PrintCount++ )
        {
            if( PrintCount == 0)   // space between fields 
            {
                fsprint(" ");
            }
            else if( PrintCount  % 8 == 0)
            {
                fsprint(" ");
            }    
            fsprint(" ");
        }
        // print PrintCount characters
        n = 0;
        for( n = 0 ; (PrintCount <= 0xf) && (n < m) ; n++,PrintCount++)
        {
            if((*tmpptr1 >=0x20) && (*tmpptr1 <= 0x7e))
                fsprint("%c",*tmpptr1);
            else
                fsprint(".");
            tmpptr1++;
        }
    }
    
    // print the body    
    PrintCount = 0;
    for (   ; i < bufferSize ; i++)
    {
        if( PrintCount == 0 )
        {
            fsprint("\n%016llx",((LLU)Address & ~0x0f));
            tmpptr1 = tmpptr0;
        }
        if(PrintCount % 8 == 0)
        {
            fsprint(" ");
        }
        fsprint(" %02x",(unsigned char)(*tmpptr0++));
        Address++;
        PrintCount ++;
        if( PrintCount  > 0x0f)  
        {
            PrintCount = 0;
            for( j = 0 ; j < 16 ; j++)
            {
                if( j == 0 ) printf("  ");
                if((*tmpptr1 >=0x20) && (*tmpptr1 <= 0x7e))
                    fsprint("%c",*tmpptr1);
                else
                    fsprint(".");
                tmpptr1++;
            }
        }
    }
    
    // print out the last space 
    m = PrintCount;
    for (      ; (PrintCount <= 0x0f) ; PrintCount++ )
    {
        if( PrintCount  % 8 == 0)
        {
            fsprint(" ");
        }    
        fsprint("   ");
    }
    
    // print PrintCount characters
    for( n = 0 ; (n < m) ; n++)
    {
        if( n == 0 ) printf("  ");
        if((*tmpptr1 >=0x20) && (*tmpptr1 <= 0x7e))
            fsprint("%c",*tmpptr1);
        else
            fsprint(".");
        tmpptr1++;
    }
    fsprint("\n");
}

#endif


static inline void Print_rte_memzone(int indent, const struct rte_memzone *m);
static inline void Print_rte_memzone(int indent, const struct rte_memzone *m)
{
    INDENT(indent);
//    char s[64]= {0};
//    int i;
//    for ( i = 0 ; i < (INDENT_SIZE * indent) ; i++) s[i] = ' ';

    printf("%s struct rte_memzone: %p\n",s,m);            
    printf("%s name        %s       \n" ,s,m->name);        //char 	name [RTE_MEMZONE_NAMESIZE]
    printf("%s len         %lu      \n" ,s,m->len);         // size_t 	len
    printf("%s hugepage_sz %lu      \n" ,s,m->hugepage_sz); // uint64_t 	hugepage_sz
    printf("%s socket_id   %u       \n" ,s,m->socket_id);   // int32_t 	socket_id
    printf("%s flags       0x%08x   \n" ,s,m->flags);       // uint32_t 	flags
    printf("%s phys_addr   %lu      \n" ,s,m->phys_addr);   // phys_addr_t 	phys_addr
    printf("%s iova        %lu      \n" ,s,m->iova);        // rte_iova_t 	iova
    printf("%s addr        %p       \n" ,s,m->addr);        // void * 	addr
    printf("%s addr_64     %lu      \n" ,s,m->addr_64);     // uint64_t 	addr_64
}


static inline void Print_rte_mempool_cache(int indent,  struct rte_mempool_cache *m);
static inline void Print_rte_mempool_cache(int indent,  struct rte_mempool_cache *m)
{  
    INDENT(indent);
 //    char s[64]= {0};
 //   int i;
 //   for ( i = 0 ; i < (INDENT_SIZE * indent) ; i++) s[i] = ' ';

    printf("%s struct rte_mempoolcache: %p\n",s,m);            
    printf("%s size         %u   \n"         ,s,m->size);             
    printf("%s flushthresh  %u   \n"         ,s,m->flushthresh);             
    printf("%s len          %u   \n"         ,s,m->len); 
    // this is a much larger array.  
    // void * 	objs [RTE_MEMPOOL_CACHE_MAX_SIZE *3]            
    printf("%s objs[0]      %p   \n"         ,s,m->objs[0] );     //void * 	pool_config
}           
            
            

static inline void Print_rte_mempool(int indent, struct rte_mempool * m);
static inline void Print_rte_mempool(int indent, struct rte_mempool * m)
{
   INDENT(indent);
   // char s[64]= {0};
   // int i;
   // for ( i = 0 ; i < (INDENT_SIZE * indent) ; i++) s[i] = ' ';

    printf("%s struct rte_mempool:  %p \n"  ,s,m);            
    printf("%s name:             %s    \n"  ,s,m->name);             //char 	name [RTE_MEMZONE_NAMESIZE]
    printf("%s pool_config       %p    \n"  ,s,m->pool_config );     //void * 	pool_config
    Print_rte_memzone( (indent + 1) ,m->mz);         //struct rte_memzone * 	mz
    printf("%s flags             0x%016x \n"  ,s,m->flags );               //unsigned int     flags  
    printf("%s socket_id         %d  \n"      ,s,m->socket_id );           //int 	socket_id
    printf("%s size              %u  \n"      ,s,m->size );                //uint32_t 	size
    printf("%s cache_size        %u  \n"      ,s,m->cache_size );          //uint32_t 	cache_size
    printf("%s elt_size          %u  \n"      ,s,m->elt_size );            //uint32_t 	elt_size
    printf("%s header_size       %u  \n"      ,s,m->header_size );         //uint32_t 	header_size
    printf("%s trailer_sizei     %u  \n"      ,s,m->trailer_size );        //uint32_t 	trailer_size
    printf("%s private_data_size %u  \n"      ,s,m->private_data_size );  //unsigned 	private_data_size
    printf("%s ops_index         %u  \n"      ,s,m->ops_index );           //int32_t 	ops_index
    Print_rte_mempool_cache( (indent + 1),m->local_cache );                     //struct rte_mempool_cache * 	local_cache
    printf("%s populated_size    %u  \n"      ,s,m->populated_size );      //uint32_t 	populated_size
    printf("%s ??? struct rte_mempool_objhdr_list??\n",s);           //struct rte_mempool_objhdr_list 	elt_list
    printf("%s nb_mem_chunks     %u  \n"      ,s,m->nb_mem_chunks );       //uint32_t 	nb_mem_chunks
    printf("%s ??? struct rte_mempool_memhdr_list ??\n",s);          //struct rte_mempool_memhdr_list 	mem_list
    printf("%s pool_data         %p  \n"      ,s,m->pool_data );           //void * 	pool_data
    printf("%s pool_id           %ld \n"      ,s,m->pool_id);              //uint64_t 	pool_id
}



/*  
 *  dumps the packet data in an rte_mbuff to the screenxi
 *
 *  https://doc.dpdk.org/guides/prog_guide/mbuf_lib.html
 */
static inline void Print_rte_mbuf_pkt(int indent, struct rte_mbuf *m);
static inline void Print_rte_mbuf_pkt(int indent, struct rte_mbuf *m)
{
    struct rte_ether_hdr *eth_hdr;
    char  src_mac[32];
    char  dst_mac[32];
    uint16_t  eth_hdr_type;    // the 16 bits after the Mac Address
    void * l3;
    struct rte_ipv4_hdr *ipv4_hdr;
    INDENT(indent);    

//  the packet date
     eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
     l3 = (uint8_t *)eth_hdr + sizeof(struct rte_ether_hdr);

     printf("%s L2/MAC Hdr):  \n",s);
     rte_ether_format_addr(dst_mac,32,&eth_hdr->d_addr);
     rte_ether_format_addr(src_mac,32,&eth_hdr->s_addr);
     eth_hdr_type = RTE_STATIC_BSWAP16(eth_hdr->ether_type);
     printf("%s dest:  %s\n",s,dst_mac);
     printf("%s src:   %s\n",s,src_mac);
     if(eth_hdr_type == RTE_ETHER_TYPE_VLAN )  // we have a packet with a vlan (0x8100)
     {
         printf("%s BUG- WE HAVE A VLAN NEED TO ADD CODE. \n",s);
         printf("%s ether_type:  0x%04x  86dd-IPV6  \n",s,eth_hdr_type);
     }
     else if (eth_hdr_type == RTE_ETHER_TYPE_ARP)
     {
          printf("%s ether_type: arp  0x%04x\n",s,eth_hdr_type);
          PrintBuff((uint8_t *)l3, 32);  // dump the next 32 bytes


     }
     else if (eth_hdr_type == RTE_ETHER_TYPE_IPV4)
     {
          char  src_ip[32];
          char  dst_ip[32];

          printf("%s ether_type: IPV4  0x%04x\n",s,eth_hdr_type);

          ipv4_hdr = (struct rte_ipv4_hdr *)l3;

          PrintBuff((uint8_t *) l3, 32);  // dump the next 32 bytes

          printf("%s L3/IP Hdr:  \n",s);
          format_ip_addr(src_ip,RTE_STATIC_BSWAP32(ipv4_hdr->src_addr));
          format_ip_addr(dst_ip,RTE_STATIC_BSWAP32(ipv4_hdr->dst_addr));
          printf("%s version ihl:     0x%02x \n",s,ipv4_hdr->version_ihl);
          printf("%s type of service: 0x%02x \n",s,ipv4_hdr->type_of_service);
      }
      else
      {
          if(m->next == NULL)
          {
              printf("%s unrecognized packet type: 0x%04x  size: %d \n",s,eth_hdr_type,rte_pktmbuf_data_len(m));
              PrintBuff((uint8_t *)eth_hdr,rte_pktmbuf_data_len(m));
          }          
          else
          {
              
              printf("%s unrecognized packet type: 0x%04x  1st data size: %d \n",s,eth_hdr_type,rte_pktmbuf_pkt_len(m));
              PrintBuff((uint8_t *)eth_hdr,rte_pktmbuf_data_len(m));
 
          }
      }
}




/*  
 *  dumps a rte_mbuff to the screeni
 *
 *  https://doc.dpdk.org/guides/prog_guide/mbuf_lib.html
 */
static inline void Print_rte_mbuf(int indent, struct rte_mbuf *m);
static inline void Print_rte_mbuf(int indent, struct rte_mbuf *m)
{
//     struct rte_ipv6_hdr *ipv6_hdr;
    INDENT(indent);    

     printf("%s \n",s);
     printf("%s == rte_mbuf:  %p\n",s,m);
//  pool information
     Print_rte_mempool((indent+1),m->pool);
     printf("%s rte_mempool->next   %p  \n",s,m->next);
//  the packet date
     Print_rte_mbuf_pkt( indent+1, m);
}

static inline void print_rte_eth_dev_portconf( int indent, struct rte_eth_dev_portconf *d);
static inline void print_rte_eth_dev_portconf( int indent, struct rte_eth_dev_portconf *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_dev_portconf { \n",s);
   printf("%s burst_size: 0x%02x\n",s,d->burst_size);
   printf("%s ring_size: 0x%02x\n",s,d->ring_size);
   printf("%s nb_queues: 0x%02x\n",s,d->nb_queues);
   printf("%s } \n",s);
 
}
 

static inline void print_rte_eth_rxmode( int indent, struct rte_eth_rxmode *d);
static inline void print_rte_eth_rxmode( int indent, struct rte_eth_rxmode *d)
{
   INDENT(indent);

   printf("%s rte_eth_rxmode { \n",s);
   printf("%s mq_mode:          0x%02x\n",s,d->mq_mode);
   printf("%s max_rx_pkt_len:   0x%08x\n",s,d->max_rx_pkt_len);
   printf("%s max_lro_pkt_size: 0x%08x\n",s,d->max_lro_pkt_size);
   printf("%s split_hdr_size    0x%04x\n",s,d->split_hdr_size);
   printf("%s offloads        0x%016lx\n",s,d->offloads);
   printf("%s reserved_64s[0]        0x%016lx\n",s,d->reserved_64s[0]);
   printf("%s reserved_64s[1]        0x%016lx\n",s,d->reserved_64s[1]);
   printf("%s reserved_ptrs[0]        %p\n",s,d->reserved_ptrs[0]);
   printf("%s reserved_ptrs[1]        %p\n",s,d->reserved_ptrs[1]);
   printf("%s } \n",s);
}
 

static inline void print_rte_eth_txmode( int indent, struct rte_eth_txmode *d);
static inline void print_rte_eth_txmode( int indent, struct rte_eth_txmode *d)
{
   INDENT(indent);

   printf("%s rte_eth_txmode { \n",s);
   printf("%s mq_mode:          0x%02x\n",s,d->mq_mode);
   printf("%s offloads        0x%016lx\n",s,d->offloads);
   printf("%s pvid              0x%04x\n",s,d->pvid);

   printf("%s hw_vlan_reject_tagged:   0x%02x\n",s,d->hw_vlan_reject_tagged);

   printf("%s reserved_64s[0]        0x%016lx\n",s,d->reserved_64s[0]);
   printf("%s reserved_64s[1]        0x%016lx\n",s,d->reserved_64s[1]);
   printf("%s reserved_ptrs[0]        %p\n",s,d->reserved_ptrs[0]);
   printf("%s reserved_ptrs[1]        %p\n",s,d->reserved_ptrs[1]);
   printf("%s } \n",s);
}
 







static inline void print_rte_eth_thresh(int indent, struct rte_eth_thresh *d);
static inline void print_rte_eth_thresh(int indent, struct rte_eth_thresh *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_thresh { \n",s);
   printf("%s pthresh: 0x%02x\n",s,d->pthresh);
   printf("%s hthresh: 0x%02x\n",s,d->hthresh);
   printf("%s wthresh: 0x%02x\n",s,d->wthresh);
   printf("%s } \n",s);
}
  
 
static inline void print_rte_eth_rxconf( int indent, struct rte_eth_rxconf *d);
static inline void print_rte_eth_rxconf( int indent, struct rte_eth_rxconf *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_rxconf { \n"              ,s);
   print_rte_eth_thresh(indent+1,&(d->rx_thresh)); 
   printf("%s rx_free_thresh:    0x%04x \n"   ,s,d->rx_free_thresh);
   printf("%s rx_drop_en:        0x%02x \n"  ,s,d->rx_drop_en);
   printf("%s rx_deferred_start: 0x%02x \n"  ,s,d->rx_deferred_start);
   printf("%s offloads:          0x%016lx \n",s,d->offloads);
   printf("%s } \n",s);
}                  
                   
static inline void print_rte_eth_txconf( int indent, struct rte_eth_txconf *d);
static inline void print_rte_eth_txconf( int indent, struct rte_eth_txconf *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_txconf { \n"              ,s);
   print_rte_eth_thresh(indent+1, &(d->tx_thresh)); 
   printf("%s tx_rs_thresh:      0x%04x\n"   ,s,d->tx_rs_thresh);
   printf("%s tx_free_thresh:    0x%02x \n"  ,s,d->tx_free_thresh);
   printf("%s tx_deferred_start: 0x%02x \n"  ,s,d->tx_deferred_start);
   printf("%s offloads:          0x%016lx \n",s,d->offloads);
   printf("%s } \n",s);
}


static inline void print_rte_eth_vmdq_dcb_conf (int indent, struct rte_eth_vmdq_dcb_conf *d);
static inline void print_rte_eth_vmdq_dcb_conf (int indent, struct rte_eth_vmdq_dcb_conf *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_vmdq_dcb_conf { \n"              ,s);
   printf("%s nb_queue_pools:           %d\n"   ,s,d->nb_queue_pools);
   printf("%s enable_default_pool:      0x%02x\n"   ,s,d->enable_default_pool);
   printf("%s default_pool:             0x%02x\n"   ,s,d->default_pool);
   printf("%s nb_pool_maps:             0x%02x\n"   ,s,d->nb_pool_maps);
   printf("%s pool_map array size       0x%02x\n"   ,s,ETH_VMDQ_MAX_VLAN_FILTERS);
   printf("%s     pool_map[0].vlan_id          0x%04x\n"   ,s,d->pool_map[0].vlan_id);
   printf("%s     pool_map[0].pools            0x%016lx\n"  ,s,d->pool_map[0].pools);
   printf("%s dcb_tc  array size        0x%02x\n"   ,s,ETH_DCB_NUM_USER_PRIORITIES);
   printf("%s     dcb_tc[0]:                0x%02x\n"   ,s,d->dcb_tc[0]);
   printf("%s } \n",s);
}

static inline void print_rte_eth_dcb_rx_conf(int indent, struct rte_eth_dcb_rx_conf  *d);
static inline void print_rte_eth_dcb_rx_conf(int indent, struct rte_eth_dcb_rx_conf  *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_dcb_rx_conf { \n"              ,s);
   printf("%s nb_tcs:                       %d\n"   ,s,d->nb_tcs);
   printf("%s dcb_tc    size       0x%02x\n"   ,s,ETH_DCB_NUM_USER_PRIORITIES);
    {
      int i;
      for ( i = 0 ; i < ETH_DCB_NUM_USER_PRIORITIES ; i++) 
      { 
          if( (  i % 20) == 0 ) printf("\n%s",s);
          printf("%02x",d->dcb_tc[i]);
      }
      printf("\n");
   }
   printf("%s } \n",s);
}

static inline void print_rte_eth_vmdq_rx_conf(int indent, struct rte_eth_vmdq_rx_conf  *d);
static inline void print_rte_eth_vmdq_rx_conf(int indent, struct rte_eth_vmdq_rx_conf  *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_vmdq_rx_conf { \n"              ,s);
   printf("%s nb_queue_pools:        %d\n"   ,s,d->nb_queue_pools);
   printf("%s enable_default_pool    0x%02x\n"   ,s,d->enable_default_pool);
   printf("%s default_pool           0x%02x\n"   ,s,d->default_pool);
   printf("%s enable_loop_back       0x%02x\n"   ,s,d->enable_loop_back);
   printf("%s nb_pool_maps           0x%02x\n"   ,s,d->nb_pool_maps);
   printf("%s rx_mode                0x%08x\n"   ,s,d->rx_mode);
   printf("%s pool_map    size       0x%02x\n"   ,s,ETH_VMDQ_MAX_VLAN_FILTERS);
   printf("%s     pool_map[0].vlan_id          0x%04x\n"   ,s,d->pool_map[0].vlan_id);
   printf("%s     pool_map[0].pools            0x%016lx\n"  ,s,d->pool_map[0].pools);
   printf("%s } \n",s);
}



static inline void print_rte_fdir_conf(int indent, struct rte_fdir_conf  *d);
static inline void print_rte_fdir_conf(int indent, struct rte_fdir_conf  *d)
{
   INDENT(indent);

   printf("%s struct rte_fdir_conf { \n"              ,s);
   printf("%s mode:             %d\n"   ,s,d->mode);
   printf("%s pballoc:          %d\n"   ,s,d->pballoc);
   printf("%s status:           %d\n"   ,s,d->status);
   printf("%s drop_queue    0x%02x\n"   ,s,d->drop_queue);
   printf("%s **** NOT FINISHED struct rte_eth_fdir_masks mask;  \n",s);
   printf("%s **** NOT FINISHED struct rte_eth_fdir_flex_conf flex_conf;  \n",s);
   printf("%s } \n",s);
}

static inline void print_rte_intr_conf(int indent, struct rte_intr_conf  *d);
static inline void print_rte_intr_conf(int indent, struct rte_intr_conf  *d)
{
   INDENT(indent);

   printf("%s struct rte_intr_conf { \n"              ,s);
   printf("%s lsc:        %d\n"   ,s,d->lsc);
   printf("%s rxq:        %d\n"   ,s,d->rxq);
   printf("%s rmv:        %d\n"   ,s,d->rmv);
   printf("%s } \n",s);
}


static inline void print_rte_eth_rss_conf( int indent, struct rte_eth_rss_conf *d);
static inline void print_rte_eth_rss_conf( int indent, struct rte_eth_rss_conf *d)
{
   INDENT(indent);

   printf("%s struct rte_eth_rss_conf { \n"              ,s);
   printf("%s rss_key:           %p\n"   ,s,d->rss_key);
   if(d->rss_key != NULL)
   {
      int i;
      for ( i = 0 ; i < 40 ; i++) 
      { 
          if( (  i % 20) == 0 ) printf("\n%s",s);
          printf("%02x",d->rss_key[i]);
      }
      printf("\n");
   }
   printf("%s rss_key_len:       0x%02x\n"   ,s,d->rss_key_len);
   printf("%s rss_hf:            0x%016lx\n"   ,s,d->rss_hf);
   printf("%s } \n",s);
}






void print_rte_eth_conf(int indent, struct rte_eth_conf *m );
void print_rte_eth_conf(int indent, struct rte_eth_conf *m )
{
   INDENT(indent);

    printf("%s struct rte_eth_conf { \n"              ,s);
    printf("%s link_speeds:      %d \n",s,m->link_speeds);  // bitmap of ETH_LINK_SPEED ???
    print_rte_eth_rxmode(indent+1 , &(m->rxmode));
    print_rte_eth_txmode(indent+1 , &(m->txmode));

    printf("%s lpbk_mode     %u (0=lpbk disabled) \n",s,m->lpbk_mode);
   

    print_rte_eth_rss_conf(indent+1 , &(m->rx_adv_conf.rss_conf ));
    print_rte_eth_vmdq_dcb_conf(indent+1 , &(m->rx_adv_conf.vmdq_dcb_conf ));
    print_rte_eth_dcb_rx_conf  ( indent+1 , &(m->rx_adv_conf.dcb_rx_conf ));
    print_rte_eth_vmdq_rx_conf (indent+1 , &(m->rx_adv_conf.vmdq_rx_conf ));

    printf("%s **** NOT FINISHED (****  \n",s);
 
    printf("%s dcb_capability_en:         0x%08x\n"   ,s,m->dcb_capability_en);


    print_rte_fdir_conf (indent+1 , &(m->fdir_conf ));
    print_rte_intr_conf (indent+1 , &(m->intr_conf ));

   printf("%s } \n",s);

}



 
/*  
 *  dumps the eth_dev_info struct
 */
static inline void Print_rte_eth_dev_info( int indent,uint16_t port_id, struct rte_eth_dev_info *d);
static inline void Print_rte_eth_dev_info( int indent,uint16_t port_id, struct rte_eth_dev_info *d)
{
   INDENT(indent);
//   char s[64]= {0};
//   int i;
//   for ( i = 0 ; i < (INDENT_SIZE * indent) ; i++) s[i] = ' ';


   printf("%s\n",s);
   printf("%sport_id: %d\n",s,port_id);
           
   printf("%s Driver Name:           %s\n"     ,s,d->driver_name);
   printf("%s index:                 0x%02x \n",s,d->if_index);
   printf("%s min_mtu:               0x%04x \n",s,d->min_mtu);
   printf("%s max_mtu:               0x%04x \n",s,d->max_mtu);
//   printf("             dev_flags: 0x%08x \n",s,d->dev_flags);
   printf("%s max_rx_pktlen:         0x%08x \n",s,d->max_rx_pktlen);
   printf("%s max_rx_queues:         0x%04x \n",s,d->max_rx_queues);
   printf("%s max_tx_queues:         0x%04x \n",s,d->max_tx_queues);
   printf("%s max_mac_addrs:         0x%08x \n",s,d->max_mac_addrs);
   printf("%s max_vfs:               0x%04x \n",s,d->max_vfs);
   printf("%s max_vmdq_pools:        0x%04x \n",s,d->max_vmdq_pools);
   printf("%s rx_offload_capa:       0x%016lx \n",s,d->rx_offload_capa);
   printf("%s tx_offload_capa:       0x%016lx \n",s,d->tx_offload_capa);
   printf("%s rx_queue_offload_capa: 0x%016lx \n",s,d->rx_queue_offload_capa);
   printf("%s tx_queue_offload_capa: 0x%016lx \n",s,d->tx_queue_offload_capa);
   printf("%s reta_size:             0x%08x \n",s,d->reta_size);
   printf("%s hash_key_size:         0x%08x \n",s,d->hash_key_size);
   print_rte_eth_rxconf(indent+1 , &(d->default_rxconf));
   print_rte_eth_txconf(indent+1 , &(d->default_txconf));
   printf("%s vmdq_queue_base:       0x%04x \n",s,d->vmdq_queue_base);
   printf("%s vmdq_queue_num:        0x%04x \n",s,d->vmdq_queue_num);
   printf("%s vmdq_pool_base:        0x%04x \n",s,d->vmdq_pool_base);
// rte_eth_desc_lim
// rte_eth_desc_lim
   printf("%s nb_rx_queues:          0x%04x \n",s,d->nb_rx_queues);
   printf("%s nb_tx_queues:          0x%04x \n",s,d->nb_tx_queues);
   print_rte_eth_dev_portconf( indent+1 ,&(d->default_rxportconf));
   print_rte_eth_dev_portconf( indent+1 , &(d->default_txportconf));
   printf("%s dev_capa:              0x%016lx \n",s,d->dev_capa);
// switch info
   printf("%s\n",s);
}


static inline void  Print_rte_eth_stats(int indent,uint16_t port_id)
{
   INDENT(indent);
 //  char s[64]= {0};
 //  int i;
 //  for ( i = 0 ; i < (INDENT_SIZE * indent) ; i++) s[i] = ' ';

    struct rte_eth_stats stats;      
    rte_eth_stats_get(port_id,&stats);
    printf("%s PortID:      %d \n",s,port_id);
    printf("%s ipackets     %lu \n",s,stats.ipackets);
    printf("%s opackets     %lu \n",s,stats.opackets);
    printf("%s ibytes       %lu \n",s,stats.ibytes);
    printf("%s obytes       %lu \n",s,stats.obytes);
    printf("%s imissed      %lu \n",s,stats.imissed);
    printf("%s ierrors      %lu \n",s,stats.ierrors);
    printf("%s oerrots      %lu \n",s,stats.oerrors);
    printf("%s rx_queue[0]  %lu \n",s,stats.q_ipackets[0]);
    printf("%s tx_queue[0]  %lu \n",s,stats.q_opackets[0]);
    printf("%s tx_queue[1]  %lu \n",s,stats.q_opackets[1]);
    printf("%s ??? q_ipackets[RTE_ETHDEV_QUEUE_STAT_CNTRS]  \n",s);
}



extern  uint32_t enabled_port_mask;

#define RSS_HASH_KEY_LENGTH  1024

// from test_pmd config.c 
static inline void Print_rss_hash_info( int port_id )
{
struct rte_eth_dev_info  dev_info;

struct rte_eth_rss_conf rss_conf = {0};
uint8_t rss_key[RSS_HASH_KEY_LENGTH];
uint8_t hash_key_size;
uint64_t rss_hf;
uint8_t i;
int diag;


    if ((enabled_port_mask & (1 << port_id)) == 0) {
            printf("\nPort is  disabled port %d\n", port_id);
            return; 
    }
    rte_eth_dev_info_get(port_id, &dev_info);

    if (dev_info.hash_key_size > 0 &&
                    dev_info.hash_key_size <= sizeof(rss_key))
            hash_key_size = dev_info.hash_key_size;
    else {
            printf("dev_info did not provide a valid hash key size\n");
            return;
    }

        /* Get RSS hash key if asked to display it */
//        rss_conf.rss_key = (show_rss_key) ? rss_key : NULL;
        rss_conf.rss_key = rss_key ;
        rss_conf.rss_key_len = hash_key_size;
        diag = rte_eth_dev_rss_hash_conf_get(port_id, &rss_conf);
        if (diag != 0) {
                switch (diag) {
                case -ENODEV:
                        printf("port index %d invalid\n", port_id);
                        break;
                case -ENOTSUP:
                        printf("operation not supported by device\n");
                        break;
                default:
                        printf("operation failed - diag=%d\n", diag);
                        break;
                }
                return;
        }
        rss_hf = rss_conf.rss_hf;
        if (rss_hf == 0) {
                printf("RSS disabled\n");
                return;
        }
        printf("RSS functions:\n ");
        for (i = 0; rss_type_table[i].str; i++) {
                if (rss_hf & rss_type_table[i].rss_type)
                        printf("%s ", rss_type_table[i].str);
        }
        printf("\n");
//        if (!show_rss_key)
//                return;
        printf("RSS key:\n");
        for (i = 0; i < hash_key_size; i++)
                printf("%02X", rss_key[i]);
        printf("\n");

}





static inline void
fs_dump_all_port_info(void)
{
uint16_t  port_id;
struct rte_eth_dev_info  dev_info;
struct rte_ether_addr m;


//struct rte_eth_conf local_port_conf = port_conf;

    RTE_ETH_FOREACH_DEV(port_id) {

            /* skip ports that are not enabled */
            if ((enabled_port_mask & (1 << port_id)) == 0) {
                    printf("\nSkipping disabled port %d\n", port_id);
                    continue;
            }

            /* init port */
         printf(" PortID:  %d) \n",port_id);
         printf("  %d  Promiscuous  (1 on, 0 off, -1 error)\n",
                                   rte_eth_promiscuous_get(port_id));
         printf("  %d  allmulticast  (1 on, 0 off, -1 error)\n",
                                        rte_eth_allmulticast_get(port_id));
         printf("  Unicast Mac Address:\n   ");
         // unicast:
         rte_eth_macaddr_get(port_id,&m);
         PrintMac(port_id,&m);

         rte_eth_dev_info_get(port_id,&dev_info);

         NEXT_COLOR();  
         Print_rte_eth_dev_info( 0,port_id,&dev_info);
         Print_rss_hash_info(port_id);



         WHITE();
    }
}
 
/*  
 *  dumps the lcore struct
 */
static inline void dump_lcore_conf(struct lcore_conf *d,int core_id);
static inline void dump_lcore_conf(struct lcore_conf *d,int core_id)
{
int i;
    printf("lcore_conf[lcore_id] for lcoreid=%d \n",core_id);
    printf("     lcore_conf[%d].n_rx_queue %d \n",core_id,d->n_rx_queue);
    printf("               rx_queue#  rx_queue_list.port_id  rx_queue_list.queue_id \n");
    for ( i = 0 ; i < d->n_rx_queue ; i ++)
    {
        printf("             %d           %d                      %d \n" ,i
                                                                         ,d->rx_queue_list[i].port_id
                                                                         ,d->rx_queue_list[i].queue_id );
    }

//   printf("     lcore_id[%d].n_rx_queue %d \n" ,lcore_id,n_rx_queue);
    printf("     lcore_conf[%d].n_tx_port  %d \n" ,core_id,d->n_tx_port);

    printf("              tx_port#     tx_port_id  tx_queue_id \n");
    for ( i = 0 ; i < d->n_tx_port ; i ++)
    {
        printf("               %d           %d           %d     \n" ,i
                                                                    ,d->tx_port_id[i]
                                                                    ,d->tx_queue_id[i] );
    }
}

static inline void 
fs_dump_all_lcore_conf(void)
{
int lcore_id;

    for (lcore_id = 0; lcore_id < RTE_MAX_LCORE; lcore_id++) {
                if (rte_lcore_is_enabled(lcore_id) == 0)
                        continue;
                NEXT_COLOR();  
                dump_lcore_conf(&(lcore_conf[lcore_id]),lcore_id);
                WHITE();
        }
}

// ROVER  P5P1  00:0e:1e:50:f7:70
static uint64_t  printcount = 0;
static uint64_t  ip_printcount = 0;
static struct rte_ether_addr P5P1 = {
                 .addr_bytes[0]=0x00 ,
                 .addr_bytes[1]=0x0e ,
                 .addr_bytes[2]=0x1e ,
                 .addr_bytes[3]=0x50 ,
                 .addr_bytes[4]=0xf7 ,
                 .addr_bytes[5]=0x70 ,
                 } ;

static struct rte_ether_addr pcap1 = {
                 .addr_bytes[0]=0x00 ,  /* msb */
                 .addr_bytes[1]=0xaa ,
                 .addr_bytes[2]=0xaa ,
                 .addr_bytes[3]=0x00 ,
                 .addr_bytes[4]=0x01 ,
                 .addr_bytes[5]=0x00 , /* lsb */
                 } ;




// fs_add_mac_address(qconf->tx_port_id[0]);
static inline void  
fs_add_mac_address(int port_id)
{
       int result;
       char string[32] ={0};
        struct rte_ether_addr mac_addr;

//       memcpy(&mac_addr,&p5p1,sizeof(struct rte_ether_addr));

       memcpy(&mac_addr,&pcap1,sizeof(struct rte_ether_addr));

       format_mac_addr(string,&mac_addr);
       printf("*** Add Mac Addr: %s  on port %d  ***\n",string,port_id);
       printf("    %sOn Rover:\n",C_GREEN);
       printf("        - Add Route\n");
       printf("             ip route add  192.168.10.0/24 dev p5p1\n");
       printf("        - Add arp\n");
       printf("             arp -s 192.168.10.12 %s  \n",string);
       printf("        - To send 1 packet  \n");
       printf("             ping  192.168.10.12 -c 1  %s\n",C_WHITE);

       result = rte_eth_dev_mac_addr_add( port_id , &mac_addr ,0);

       if ( result != 0)
        {
            printf("------ Error calling rte_eth_dev_mac_addr_add(): %d\n",result);
        }
}



// returns 0 if the mac does not match, 1 if it does,  negative if error
//       src_dest   0 = src, 1=dest, 2, either
//       mac        
//       pkt
//       verbose
static inline int fs_id_packet_by_mac(int src_dest,struct rte_ether_addr *mac,struct rte_mbuf *m, int verbose);
static inline int fs_id_packet_by_mac(int src_dest,struct rte_ether_addr *mac,struct rte_mbuf *m, int verbose)
{
     struct rte_ether_hdr *eth_hdr;
     char  src_mac[32];
     char  dst_mac[32];

     eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
     if(verbose >= 3) printf("%d:%s:%s\n",__LINE__,__FILE__,__FUNCTION__);

     if(verbose >= 2) 
     {
          printf("    L2/MAC Hdr):  \n");
          rte_ether_format_addr(dst_mac,32,&eth_hdr->d_addr);
          rte_ether_format_addr(src_mac,32,&eth_hdr->s_addr);
          printf("     dest:  %s\n",dst_mac);
          printf("     src:   %s\n",src_mac);
      }

      if (src_dest == 0)  // check src 
      {
            	if ( rte_is_same_ether_addr (&eth_hdr->s_addr, mac) == 1)
                {
                    if(verbose >= 1)
                    {
                       rte_ether_format_addr(src_mac,32,&eth_hdr->s_addr); 
                       printf("%ld SRC Mac Match: %s \n",printcount,src_mac);
                       printcount++;
                    }
                    return 1;
                }
                return 0;
      } 
      else if (src_dest == 1) // check dest
      {
             	if ( rte_is_same_ether_addr (&eth_hdr->d_addr, mac) == 1)
                {
                    if(verbose >= 1)
                    {
                       rte_ether_format_addr(dst_mac,32,&eth_hdr->d_addr); 
                       printf("%ld DST Mac Match: %s \n",printcount,dst_mac);
                       printcount++;
                    }
                    return 1;
                }
                return 0;
      } 
      else if (src_dest == 2) // check src and dest mac
      {
                int flag = 0;
            	if ( rte_is_same_ether_addr (&eth_hdr->s_addr, mac) == 1)
                {
                    if(verbose >= 1)
                    {
                       rte_ether_format_addr(src_mac,32,&eth_hdr->s_addr); 
                       printf("%ld 2_SRC Mac Match: %s \n",printcount,src_mac);
                       printcount++;
                    }
                    flag = 1;
                }
             	if ( rte_is_same_ether_addr (&eth_hdr->d_addr, mac) == 1)
                {
                    if(verbose >= 1)
                    {
                       rte_ether_format_addr(dst_mac,32,&eth_hdr->d_addr); 
                       printf("%ld 2_DST Mac Match: %s \n",printcount,dst_mac);
                       printcount++;
                    }
                    flag=1;
                }
                if ( flag == 1 ) return 1;
                return 0;
 
     } 
     return -1;

}


// returns 0 if the ip does not match, 1 if it does,  negative if error
//       src_dest   0 = src, 1=dest, 2, either
//       ipv4        
//       pkt
//       verbose
static inline int fs_id_packet_by_IPv4(int src_dest,uint32_t IPv4,struct rte_mbuf *m, int verbose);
static inline int fs_id_packet_by_IPv4(int src_dest,uint32_t IPv4,struct rte_mbuf *m, int verbose)

 {
     struct rte_ether_hdr *eth_hdr;
     uint16_t  eth_hdr_type;    // the 16 bits after the Mac Address
     void * l3;
     struct rte_ipv4_hdr *ipv4_hdr;
     uint32_t src_ip=0;
     uint32_t dst_ip=0;
 //     struct rte_ipv6_hdr *ipv6_hdr;
     INDENT(0);

 //  the packet date
      eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
      l3 = (uint8_t *)eth_hdr + sizeof(struct rte_ether_hdr);
      eth_hdr_type = RTE_STATIC_BSWAP16(eth_hdr->ether_type);

      if(eth_hdr_type == RTE_ETHER_TYPE_VLAN )  // we have a packet with a vlan (0x8100)
      {
          if(verbose >=  2)
          {
              printf("%s BUG- WE HAVE A VLAN NEED TO ADD CODE. \n",s);
              printf("%s ether_type:  0x%04x  86dd-IPV6  \n",s,eth_hdr_type);
          }
      }
      else if (eth_hdr_type == RTE_ETHER_TYPE_ARP)
      {
          if(verbose >=  2)
          {
              printf("%s ether_type: arp  0x%04x\n",s,eth_hdr_type);
          }

      }
      else if (eth_hdr_type == RTE_ETHER_TYPE_IPV4)
      {
           if(verbose >=  2)
           { 
               printf("%s ether_type: IPV4  0x%04x\n",s,eth_hdr_type);
               printf("%s looking for IP address:  0x%08x\n",s,IPv4);
           } 
           ipv4_hdr = (struct rte_ipv4_hdr *)l3;
           src_ip = (ipv4_hdr->src_addr);
           dst_ip = (ipv4_hdr->dst_addr);
           if(verbose >=  2)
           {
                printf("%s src_ip:  0x%08x\n",s,src_ip);
                printf("%s dst_ip:  0x%08x\n",s,dst_ip);
           }
//           printf("%s L3/IP Hdr:  \n",s);
//           format_ip_addr(src_ip,RTE_STATIC_BSWAP32(ipv4_hdr->src_addr));
//           format_ip_addr(dst_ip,RTE_STATIC_BSWAP32(ipv4_hdr->dst_addr));
//           printf("%s version ihl:     0x%02x \n",s,ipv4_hdr->version_ihl);
//           printf("%s type of service: 0x%02x \n",s,ipv4_hdr->type_of_service);
       }
       else
       {
           if(verbose >=  2)
           { 
               printf("%s unrecognized packet type %d (0x%04x)\n",s,eth_hdr_type,eth_hdr_type);
           }
           if(verbose >=  3)
           { 
              // Print_rte_mbuf_pkt(int indent, struct rte_mbuf *m)
                Print_rte_mbuf_pkt( 3 , m);
           }
       }

     if(verbose >= 3) printf("%d:%s:%s\n",__LINE__,__FILE__,__FUNCTION__);

      if (src_dest == 0)  // check src 
      {
            	if ( IPv4  == src_ip)
                {
                    if(verbose >= 1)
                    {
                       printf("%s src_ip:  0x%08x\n",s,src_ip);
                       ip_printcount++;
                    }
                    return 1;
                }
                return 0;
      } 
      else if (src_dest == 1) // check dest
      {
             	if ( IPv4 == dst_ip)
                {
                    if(verbose >= 1)
                    {
                       printf("%s dst_ip:  0x%08x\n",s,dst_ip);
                       ip_printcount++;
                    }
                    return 1;
                }
                return 0;
      } 
      else if (src_dest == 2) // check src and dest mac
      {
                int flag = 0;
            	if ( src_ip == IPv4)
                {
                    if(verbose >= 1)
                    {
                       printf("%s src_ip:  0x%08x\n",s,src_ip);
                       ip_printcount++;
                    }
                    flag = 1;
                }
             	if ( dst_ip == IPv4 )
                {
                    if(verbose >= 1)
                    {
                       printf("%s dst_ip:  0x%08x\n",s,dst_ip);
                       ip_printcount++;
                    }
                    flag=1;
                }
                if ( flag == 1 ) return 1;
                return 0;
 
     } 
     return -1;

}


static inline int fs_get_packet_type (uint16_t *pktType ,struct rte_mbuf *m, int verbose);
static inline int fs_get_packet_type (uint16_t *pktType ,struct rte_mbuf *m, int verbose)
{
     struct rte_ether_hdr *eth_hdr;
     uint16_t  eth_hdr_type;    // the 16 bits after the Mac Address
//     struct rte_ipv6_hdr *ipv6_hdr;

     eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);

     eth_hdr_type = RTE_STATIC_BSWAP16(eth_hdr->ether_type);

     if( verbose >= 1)  printf(" L3 header type: 0x%04x \n",eth_hdr_type);

     if( pktType != NULL) *pktType = eth_hdr_type;

     return 0;
}



typedef struct Struct_fs_PktData {
       struct rte_ether_addr   src_mac;
       struct rte_ether_addr   dst_mac;
       uint16_t                ether_type;
       uint32_t  src_ip;
       uint32_t  dst_ip;
       uint8_t   protocol;    // udp,tcp,icmp, ...
       uint16_t  udp_src_port;
       uint16_t  udp_dst_port;
       uint16_t  udp_len;
       uint16_t  udp_cs;
       uint8_t * pkt_data;    // udp,tcp,icmp, ...
       uint32_t  nb_pkt_data;
} fs_PktData;



static inline int fs_get_packet_info (fs_PktData *pktType ,struct rte_mbuf *m, int verbose);
static inline int fs_get_packet_info (fs_PktData *pktType ,struct rte_mbuf *m, int verbose)
{
     struct rte_ether_hdr *eth_hdr;
     uint16_t  eth_hdr_type;    // the 16 bits after the Mac Address
     void * l3;
     struct rte_ipv4_hdr *ipv4_hdr;
     uint8_t  protocol;
 //     struct rte_ipv6_hdr *ipv6_hdr;
     INDENT(0);

 //  the MAC Header Info
      eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
      rte_ether_addr_copy ( &(eth_hdr->d_addr) , &(pktType->src_mac));
      rte_ether_addr_copy ( &(eth_hdr->s_addr) , &(pktType->dst_mac));
      pktType->ether_type = eth_hdr->ether_type; // not clear how this takes into account vlan?? 

     if(verbose >= 2) 
     {
          char  src_mac[32];
          char  dst_mac[32];
        
          printf("    L2/MAC Hdr):  \n");
          rte_ether_format_addr(dst_mac,32,&eth_hdr->d_addr);
          rte_ether_format_addr(src_mac,32,&eth_hdr->s_addr);
          printf("     dest:         %s\n",dst_mac);
          printf("     src:          %s\n",src_mac);
          printf("     ether_type:   %s\n",src_mac);
     }

     eth_hdr_type = RTE_STATIC_BSWAP16(eth_hdr->ether_type);
     switch (   eth_hdr_type ) {
       case RTE_ETHER_TYPE_IPV4 :     //0x0800
            if( verbose >= 2) printf("  l2 header type: ETHER_TYPE_IPv4  0x%04x\n",eth_hdr_type);

            l3 = (uint8_t *)eth_hdr + sizeof(struct rte_ether_hdr);
            ipv4_hdr = (struct rte_ipv4_hdr *)l3;
            pktType->src_ip      = ipv4_hdr->src_addr ;
            pktType->dst_ip      = ipv4_hdr->dst_addr ;
            pktType->protocol    = ipv4_hdr->next_proto_id;
            if(verbose >=  2)
            {
                printf("%s src_ip:  0x%08x\n",s,pktType->src_ip);
                printf("%s dst_ip:  0x%08x\n",s,pktType->dst_ip);
            }
//           printf("%s L3/IP Hdr:  \n",s);
//           format_ip_addr(src_ip,RTE_STATIC_BSWAP32(ipv4_hdr->src_addr));
//           format_ip_addr(dst_ip,RTE_STATIC_BSWAP32(ipv4_hdr->dst_addr));
//           printf("%s version ihl:     0x%02x \n",s,ipv4_hdr->version_ihl);
//           printf("%s type of service: 0x%02x \n",s,ipv4_hdr->type_of_service);
            
            protocol =  ipv4_hdr->next_proto_id ; 
            switch ( protocol ) {
                 case 0x06:     //TCP  6
                     if( verbose >= 2) printf("  l4 - UDP  0x%02x\n",protocol);
                     break;
                 case 0x11:     //UDP  17
                     if( verbose >= 2) printf("  l4 - TCP  0x%02x\n",protocol);
                     break;
                 case 50:     //ESC  50
                     if( verbose >= 2) printf("  l4 - ESC  0x%02x\n",protocol);
                     break;
                 default:
                     if( verbose >= 2) printf("  l4 unknown  0x%02x\n",protocol);
                     break;
                } // end ipv4 payload types. 
            
 
            break;

       case RTE_ETHER_TYPE_IPV6 :     //0x86DD
            if( verbose >= 2) printf("  l2 header type: ETHER_TYPE_IPv6  0x%04x\n",eth_hdr_type);
            break;

       case RTE_ETHER_TYPE_ARP :     //0x0806
            if( verbose >= 2) printf("  l2 header type: ETHER_TYPE_ARP  0x%04x\n",eth_hdr_type);
            break;

       case RTE_ETHER_TYPE_RARP :     //0x8035
            if( verbose >= 2) printf("  l2 header type: ETHER_TYPE_RARP  0x%04x\n",eth_hdr_type);
            break;

       case RTE_ETHER_TYPE_VLAN :     //0x8100
            if( verbose >= 2) printf("  l2 header type: ETHER_TYPE_VLAN  0x%04x\n",eth_hdr_type);
            break;

       case RTE_ETHER_TYPE_1588 :     //0x88f7
            if( verbose >= 2) printf("  l2 header type: ETHER_TYPE_1588  0x%04x\n",eth_hdr_type);
            break;

       default:
            printf(" unrecognized l2 eth header type 0x%04x\n",eth_hdr_type);
            break;
       }  // end mac ether_type  
  


     return 0;
}

// rte_pktmbuf_free(m);


static inline int fs_send_packet(struct rte_mbuf *m, int16_t tx_port_id,int16_t tx_queue_id , int verbose);
static inline int fs_send_packet(struct rte_mbuf *m, int16_t tx_port_id,int16_t tx_queue_id , int verbose)
{
struct rte_mbuf **am;
int16_t result;

     am = &m;
     result = rte_eth_tx_burst ( tx_port_id,tx_queue_id, am, 1);
     if(verbose >=2) printf(" fs_send_packet_result: %d \n", result )	;
    return result;

#if 0
    // should check to see if the 
78 static inline void
 79 l3fwd_lpm_no_opt_send_packets(int nb_rx, struct rte_mbuf **pkts_burst,
 80                                 uint16_t portid, struct lcore_conf *qconf)
 81 {
 82         int32_t j;
 83
 84         /* Prefetch first packets */
 85         for (j = 0; j < PREFETCH_OFFSET && j < nb_rx; j++)
 86                 rte_prefetch0(rte_pktmbuf_mtod(pkts_burst[j], void *));
 87
 88         /* Prefetch and forward already prefetched packets. */
 89         for (j = 0; j < (nb_rx - PREFETCH_OFFSET); j++) {
 90                 rte_prefetch0(rte_pktmbuf_mtod(pkts_burst[
 91                                 j + PREFETCH_OFFSET], void *));
 92                 l3fwd_lpm_simple_forward(pkts_burst[j], portid, qconf);
 93         }
 94
 95         /* Forward remaining prefetched packets */
 96         for (; j < nb_rx; j++)
 97                 l3fwd_lpm_simple_forward(pkts_burst[j], portid, qconf);
 98 }

 8 static __rte_always_inline void
  9 l3fwd_lpm_simple_forward(struct rte_mbuf *m, uint16_t portid,
 10                 struct lcore_conf *qconf)
 11 {
 12         struct rte_ether_hdr *eth_hdr;
 13         struct rte_ipv4_hdr *ipv4_hdr;
 14         uint16_t dst_port;
 15
 16         eth_hdr = rte_pktmbuf_mtod(m, struct rte_ether_hdr *);
 17
 18         if (RTE_ETH_IS_IPV4_HDR(m->packet_type)) {
 19                 /* Handle IPv4 headers.*/
 20                 ipv4_hdr = rte_pktmbuf_mtod_offset(m, struct rte_ipv4_hdr *,
 21                                                 sizeof(struct rte_ether_hdr));
 22
 23 #ifdef DO_RFC_1812_CHECKS
 24                 /* Check to make sure the packet is valid (RFC1812) */
 25                 if (is_valid_ipv4_pkt(ipv4_hdr, m->pkt_len) < 0) {
 26                         rte_pktmbuf_free(m);
 27                         return;
 28                 }
 29 #endif
 30                  dst_port = lpm_get_ipv4_dst_port(ipv4_hdr, portid,
 31                                                 qconf->ipv4_lookup_struct);
 32
 33                 if (dst_port >= RTE_MAX_ETHPORTS ||
 34                         (enabled_port_mask & 1 << dst_port) == 0)
 35                         dst_port = portid;
 36
 37 #ifdef DO_RFC_1812_CHECKS
 38                 /* Update time to live and header checksum */
 39                 --(ipv4_hdr->time_to_live);
 40                 ++(ipv4_hdr->hdr_checksum);
 41 #endif
 42                 /* dst addr */
 43                 *(uint64_t *)&eth_hdr->d_addr = dest_eth_addr[dst_port];
 44
 45                 /* src addr */
 46                 rte_ether_addr_copy(&ports_eth_addr[dst_port],
 47                                 &eth_hdr->s_addr);
 48
 49                 send_single_packet(qconf, m, dst_port);
 50         } else if (RTE_ETH_IS_IPV6_HDR(m->packet_type)) {
 51                 /* Handle IPv6 headers.*/
 52                 struct rte_ipv6_hdr *ipv6_hdr;
 53
 54                 ipv6_hdr = rte_pktmbuf_mtod_offset(m, struct rte_ipv6_hdr *,
 55                                                 sizeof(struct rte_ether_hdr));
 56
 57                 dst_port = lpm_get_ipv6_dst_port(ipv6_hdr, portid,
 58                                         qconf->ipv6_lookup_struct);
 59
 60                 if (dst_port >= RTE_MAX_ETHPORTS ||
 61                         (enabled_port_mask & 1 << dst_port) == 0)
 62                         dst_port = portid;
 63
 64                 /* dst addr */
 65                 *(uint64_t *)&eth_hdr->d_addr = dest_eth_addr[dst_port];
 66
 67                 /* src addr */
 68                 rte_ether_addr_copy(&ports_eth_addr[dst_port],
 69                                 &eth_hdr->s_addr);
 70
 71                 send_single_packet(qconf, m, dst_port);
 72         } else {
 73                 /* Free the mbuf that contains non-IPV4/IPV6 packet */
 74                 rte_pktmbuf_free(m);
 75         }
 76 }


n /* Enqueue a single packet, and send burst if queue is filled */
111 static inline int
112 send_single_packet(struct lcore_conf *qconf,
113                    struct rte_mbuf *m, uint16_t port)
114 {
115         uint16_t len;
116
117         len = qconf->tx_mbufs[port].len;
118         qconf->tx_mbufs[port].m_table[len] = m;
119         len++;
120
121         /* enough pkts to be sent */
122         if (unlikely(len == MAX_PKT_BURST)) {
123                 send_burst(qconf, MAX_PKT_BURST, port);
124                 len = 0;
125         }
126
127         qconf->tx_mbufs[port].len = len;
128         return 0;
129 }


89 /* Send burst of packets on an output interface */
 90 static inline int
 91 send_burst(struct lcore_conf *qconf, uint16_t n, uint16_t port)
 92 {
 93         struct rte_mbuf **m_table;
 94         int ret;
 95         uint16_t queueid;
 96
 97         queueid = qconf->tx_queue_id[port];
 98         m_table = (struct rte_mbuf **)qconf->tx_mbufs[port].m_table;
 99
100         ret = rte_eth_tx_burst(port, queueid, m_table, n);
101         if (unlikely(ret < n)) {
102                 do {
103                         rte_pktmbuf_free(m_table[ret]);
104                 } while (++ret < n);
105         }
106
107         return 0;
108 }

#endif 
}

/*static inline void fs_command(struct rte_mbuf *m, int verbose);
static inline void fs_command(struct rte_mbuf *m, int verbose)
{
     uint8_t ptr;

}
*/

#endif
