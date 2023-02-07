#include "tpsid_procfs.h"

static int dv_pf_open( struct inode *_i, struct file *_f) {  return( 0);  }
static int dv_pf_release(struct inode *_i, struct file *_f) {  return( 0);  }
static int dv_pf_W( struct file *_f, const char __user *_buf, size_t _cnt, loff_t *_l) {  return( 0);  }

static int dv_pf_R( struct file *_f, char __user *_buf, size_t _s, loff_t *_l) {
 unsigned char ret;
 if ( *_l > 0) return( 0);
 if ( copy_to_user( _buf, tpsid, TPSID_LEN)) return( -EFAULT);
 *_l += ret = TPSID_LEN;
 return( ret);  }

static int dv_pf_Rt( struct file *_f, char __user *_buf, size_t _s, loff_t *_l) {
 unsigned char ret;
 unsigned char buff[ TPSID_LEN*2 + 1];
 int i;
 if ( *_l > 0) return( 0);
 memset( buff, 0, TPSID_LEN*2 + 1);
 for ( i = 0; i < TPSID_LEN; i++) {
   sprintf( buff + i*2, "%02X", tpsid[ i]);
 }
 if ( copy_to_user( _buf, buff, TPSID_LEN*2)) return( -EFAULT);
 *_l += ret = TPSID_LEN*2;
 return( ret);  }

// fo_I: on/off
// fo_It: text representation
#if ( LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0))
static const struct proc_ops fo_I = {
 .proc_open = dv_pf_open,
 .proc_lseek =  no_llseek,
 .proc_release = dv_pf_release,
 .proc_read = dv_pf_R,
 .proc_write = dv_pf_W,
};
static struct proc_ops fo_It;
#else
static const struct file_operations fo_I = {
 .owner = THIS_MODULE,
 .open = dv_pf_open,
 .llseek =  no_llseek,
 .release = dv_pf_release,
 .read = dv_pf_R,
 .write = dv_pf_W,
};
static struct file_operations fo_It;
#endif

// ---------- main (exported) functions
void tpsid_procfs_init( void) {
 struct proc_dir_entry *tfs, *tfst;
 char tmps[ 10];
 fo_It = fo_I;
#if ( LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0))
 fo_It.proc_read = dv_pf_Rt;
#else
 fo_It.read = dv_pf_Rt;
#endif
 memset( tmps, 0, 10);
 sprintf( tmps, "%s", MNAME);
 tfs  = proc_create_data( tmps, 0, NULL, &fo_I, NULL);
 memset( tmps, 0, 10);
 sprintf( tmps, "%st", MNAME);
 tfst = proc_create_data( tmps, 0, NULL, &fo_It, NULL);
 return;  }

void tpsid_procfs_clean( void) {
 char tmps[ 10];
 memset( tmps, 0, 10);
 sprintf( tmps, "%s", MNAME);
 remove_proc_entry( tmps, NULL);
 memset( tmps, 0, 10);
 sprintf( tmps, "%st", MNAME);
 remove_proc_entry( tmps, NULL);
 return;  }
