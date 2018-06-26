#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

#include <linux/vmalloc.h>
#include <linux/slab.h>
#include "wl_crypto.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test Module");
MODULE_AUTHOR("user<user@gmail.com>");
MODULE_ALIAS("test");


static int __init hello_init(void)
{
   unsigned char* hash_result = kmalloc(4096, GFP_KERNEL);
   char* str_checksum = vmalloc(65*sizeof(char));
   char *input = "123456789101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899100101102103104105106107108109110111112113114115116117118119120121122123124125126127128";
   char *ctx4hash = NULL;
   int blockcnt = 0;
   int i;

   memset(hash_result, 0, 4096);
   memset(str_checksum, 0, 65);

   ctx4hash = (char*)preprocess_string(input, &blockcnt);
   get_checksum(hash_result, ctx4hash, strlen(input));

   // print sha512 result
   for(i=0;i<64;i++){
       sprintf(&str_checksum[i*2], "%02x", hash_result[i]);
       printk("%02x", hash_result[i]);
   }
   printk("\n");

   printk("I am alive.\n");
exit:
   if(ctx4hash) kfree(ctx4hash);
   return 0;    // Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
  printk(KERN_INFO "I am dead.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);

