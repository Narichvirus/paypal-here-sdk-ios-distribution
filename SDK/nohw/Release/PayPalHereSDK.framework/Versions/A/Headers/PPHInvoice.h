//
//  PPHInvoice.h
//  PayPal Here
//
//  Created by Matthew Pavlinsky on 5/23/12.
//  Copyright (c) 2012 PayPal, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/*! These could be forward declared, but I would rather them be here so the end user only needs to include PPHInvoice */
#import "PPHInvoiceConstants.h"
#import "PPHInvoiceTotals.h"
#import "PPHInvoicePayment.h"
#import "PPHInvoiceItem.h"
#import "PPHInvoiceContactInfo.h"
#import "PPHInvoiceItemContext.h"
#import "PPHInvoiceProtocol.h"

/*! Forward declarations */
@class PPHError;
@class BarcodeResult;

/*!
 * An invoice represents a collection of items and extra charges by a merchant for a customer.
 */
@interface PPHInvoice : NSObject<
    PPHInvoiceProtocol
>

#pragma mark -
#pragma mark Initialization and Exporting
/*!
 Finds the invoice's item that shares an itemId and updates it copying the attributes of the passed PPHInvoiceItem except for quantity which is used as a delta. If no item is found the passed item is added to the invoice.
 @param invoiceId NSString The ID of the invoice to fetch from the server. You can acquire an invoice ID from doing a SearchInvoices API call or using one from saving a previous invoice.
 @param context NSManagedObjectContext The context to reconcile the invoice with, nil is you would not like to reconcile at this time.
 @param completionHandler PPHInvoiceLoadCompletionHandler The block to invoke and retuirn the newly created invoice once the load is complete.
 */
+ (void)downloadInvoiceForInvoiceId:(NSString*)invoiceId context:(PPHInvoiceItemContext*)context completionHandler:(PPHInvoiceLoadCompletionHandler)completionHandler;

/*!
 Initialize the invoice with just a currency. The go to way to make a brand new invoice
 @param currency NSString The curreny code to make the invoice with.
 @return id The created invoice
 */
- (id)initWithCurrency:(NSString*)currency;

/*!
 Initialize the invoice with data received from the server in the past.
 @param representation NSDictionary The dictionary previously received from a GetInvoiceDetails API call.
 @return id The created invoice
 */
- (id)initWithDictionary:(NSDictionary *)representation;

/*!
 Initialize the invoice with data received from the server in the past and reconcile its items with the given context.
 @param representation NSDictionary The dictionary previously received from a GetInvoiceDetails API call.
 @param context NSManagedObjectContext The context to reconcile the invoice items with.
 @return id The created invoice
 */
- (id)initWithDictionary:(NSDictionary *)representation context:(PPHInvoiceItemContext*)context;

/*!
 Initialize the invoice with data received from the server in the past give it the invoice ID specified and reconcile its items with the given context. You MUST use this initialization method if you have an invoice ID that you want to give to an invoice, otherwise the invoice will get a new one when saving for the first time.
 @param representation NSDictionary The dictionary previously received from a GetInvoiceDetails API call.
 @param invoiceId NSString The invoice ID previously received from the server that you want to give to this server.
 @param context NSManagedObjectContext The context to reconcile the invoice items with.
 @return id The created invoice
 */
- (id)initWithDictionary:(NSDictionary *)representation invoiceId:(NSString*)invoiceId context:(PPHInvoiceItemContext*)context;

/*!
 Initialize a simple invoice with one item and an amount.
 @param item Item name or description
 @param amount The amount of the item
 */
- (id)initWithItem: (NSString*) item forAmount: (PPHAmount*) amount;

/*!
 Compile the invoice's data to a format that is ready to save as an InvoiceType parameter to an API call.
 @return id The created invoice
 */
- (NSDictionary*)asDictionary;


/*!
 Reloads an invoice's data using a dictionary previously received from the server.
 @param dictionary The NSDictionary as received from the server
 */
- (void)readDictionary:(NSDictionary*)dictionary;

#pragma mark
#pragma mark Monitored Fields Any changes cause the invoice to be out of sync with the server
/*! Discount applied to the subtotal (amount applied first, then percentage) */
@property (strong,nonatomic) NSDecimalNumber *discountAmount;
/*! Discount percentage applied to the subtotal (amount applied first, then percentage) */
@property (strong,nonatomic) NSDecimalNumber *discountPercentage;
/*! The amount the payer decided to tip (or the default tip) */
@property (strong,nonatomic) NSDecimalNumber *gratuity;
/*! e.g. DueOnReceipt,Net30 */
@property (strong,nonatomic) NSString *paymentTerms;
/*! Custom due date */
@property (strong,nonatomic) NSDate *dueDate;
/*! Often noreply@here.paypal.com */
@property (nonatomic,strong) NSString *payerEmail;
/*! Billing address information */
@property (strong,nonatomic,readonly) PPHInvoiceContactInfo *billingInfo;
/*! Shipping address information */
@property (strong,nonatomic,readonly) PPHInvoiceContactInfo *shippingInfo;
/*! The cost of shipping applied to the invoice */
@property (strong,nonatomic) NSDecimalNumber* shippingAmount;
/*! The actual percentage tax rate applied to the shipping */
@property (strong,nonatomic) NSDecimalNumber *shippingTaxRate;
/*! The name of the tax rate applied to the shipping cost */
@property (strong,nonatomic) NSString *shippingTaxRateName;
/*! Is the tax included in the subtotal? */
@property (nonatomic) BOOL taxInclusive;
/*! Is the discount to be subtracted before tax? */
@property (nonatomic) BOOL taxCalculatedAfterDiscount;
/*! The name of a custom value entered on an invoice from the website. */
@property (strong,nonatomic) NSString *customAmountName;
/*! The amount of a custom value entered on an invoice from the website. */
@property (strong,nonatomic) NSDecimalNumber *customAmountValue;
/*! Referrer code - used to track source of invoice creation beyond just "API/Web" */
@property (nonatomic,readonly) NSString *referrerCode;


#pragma mark -
#pragma mark Read only fields
/*! The currency type used by this invoice */
@property (strong,nonatomic,readonly) NSString *currency;


#pragma mark -
#pragma mark Convenience access to external data.
/*! The unique identifier for the invoice received when creating the invoice on the network */
@property (nonatomic,readonly) NSString *paypalInvoiceId;
/*! The date of the last save */
@property (nonatomic,readonly) NSDate* createDate;
/*! The unique number assigned to the invoice for the mercahnt that created it */
@property (nonatomic,readonly) NSString *merchantReferenceNumber;
/*! A memo from the server that contains location data of a payment */
@property (nonatomic,readonly) NSString *merchantMemo;
/*! Data about the payment of the invoice */
@property (nonatomic,strong) PPHInvoicePayment *paymentInfo;
/*! An array of PPHInvoicePayments received from the server */
@property (nonatomic,readonly) NSArray *refunds;
/*! The last received status of the invoice */
@property (nonatomic,readonly) PPHInvoiceStatus status;
/*! YES if invoice origin is Web */
@property (nonatomic,readonly) BOOL originatedOnWeb;

#pragma mark -
#pragma mark Calculated values
/*! All the calculated total information for the invoice. Gets recalculated automatically whenever a change is made to the invoice items. */
@property (strong,nonatomic,readonly) PPHInvoiceTotals* totals;

/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) PPHAmount *totalAmount;
/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) NSDecimalNumber *subTotal;
/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) NSDecimalNumber *tax;
/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) NSDecimalNumber *subTotalWithDiscounts;
/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) NSDecimalNumber *totalDiscount;
/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) NSDecimalNumber *refundTotal;
/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) NSDictionary *taxDetails;
/*! Convenience method for accessing PPHInvoiceTotals data */
@property (nonatomic,readonly) PPHAmount *totalWithRefunds;


#pragma mark -
#pragma mark Invoice Information
/*! The items in the invoice. Sorted according to display order. */
@property (nonatomic,readonly) NSArray *items;
/*! A dump of the dictionary representation of the invoice */
@property (nonatomic,readonly) NSString *description;
/*! Number of unique items in the invoice */
@property (nonatomic,readonly) int itemCount;

/*!
 * Get the quantity of an item currently on the order.
 * @param itemId the item id for the item for which a quantity is desired
 */
- (NSDecimalNumber*)quantityByItemId:(NSString*)itemId;

#pragma mark -
#pragma mark Invoice Manipulation

/*! A note that can be used when marking as paid if no other is specified. */
@property (strong,nonatomic) NSString *note;

/*!
 Fetches an invoice item that corresponds to an itemId. This can be used with itemIds for custom items you added, or a SellableItem's id.
 @param itemId NSString The itemId to find in the invoice.
 @return PPHInvoiceItem The invoice item that was found. If there was none nil is returned.
 */
- (PPHInvoiceItem*)invoiceItemWithId:(NSString*)itemId;

/*!
 Creates an invoice item with the given parameters an returns a pointer to it. ONLY use this function if you want to make an item that is not bound to a SellableItem for some reason. If you add one of these such items to the invoice and later call reconcileInContext the item will be associated with a new SellableItem and the item's itemId will be set to that of the SellableItem, rendering the previous itemId useless for searching in the invoice.
 @param itemId NSString The itemId for the new invoice. Must be unique to other invoice items. You can use this to get a pointer to the item later using invoiceWithId if you don't call reconcileInContext.
 @param name NSString The item name.
 @param quantity NSDecimalNumber The number of the items to put in the cart.
 @param unitPrice NSDecimalNumber The price of a single one of these items.
 @param taxRate NSDecimalNumber The tax to be applied to this item.
 @param taxRateName NSString The name for the tax rate given to this item.
 @return PPHInvoiceItem The newly created item.
 */
- (PPHInvoiceItem*)addItemWithId:(NSString *)itemId name:(NSString *)name quantity:(NSDecimalNumber *)quantity unitPrice:(NSDecimalNumber *)unitPrice taxRate:(NSDecimalNumber *)taxRate taxRateName:(NSString*)taxRateName;

/*!
 Adds the specified quantity to the specified InvoiceItem in the invoice, you may pass a negative quantity value to decrement the item. Calling increment on an InvoiceItem that does not exist in the invoice will cause the item to be added with the desired quantity.
 @param item PPHInvoiceItem The item to increment.
 @param quantity NSDecimalNumber The amount to increase the item's quantity by, this may be negative to remove items from the invoice.
 */
- (void)incrementInvoiceItem:(PPHInvoiceItem*)item byQuantity:(NSDecimalNumber*)quantity;

/*!
 * Remove all items from the invoice
 */
- (void)removeAllItems;

#pragma mark -
#pragma mark Networking
/*!
 Enqueues a network action to synchronize the invoice with the server's representation of it.
 @param completionHandler PPHInvoiceBasicCompletionHandler The block to invoke once the network response is processed, you can check the returned error to see if the request was successful.
 */
- (void)refreshInvoice: (PPHInvoiceBasicCompletionHandler)completionHandler;

/*!
 Enqueues a network action to save the invoice.
 @param completionHandler PPHInvoiceBasicCompletionHandler The block to invoke once the network response is processed, you can check the returned error to see if the request was successful.
 */
- (void)save:(PPHInvoiceBasicCompletionHandler)completionHandler;

/*!
 Enqueues a network action to send the invoice. A save is performed if the invoice has changed.
 @param completionHandler PPHInvoiceBasicCompletionHandler The block to invoke once the network response is processed, you can check the returned error to see if the request was successful.
 */
- (void)send:(PPHInvoiceBasicCompletionHandler)completionHandler;

/*!
 Enqueues a network action to cancel the invoice.
 @param completionHandler PPHInvoiceBasicCompletionHandler The block to invoke once the network response is processed, you can check the returned error to see if the request was successful.
 */
- (void)cancel:(PPHInvoiceBasicCompletionHandler)completionHandler;

/*!
 Enqueues a network action to get refund details
 @param completionHandler PPHInvoiceBasicCompletionHandler The block to invoke once the network response is processed, you can check the returned error to see if the request was successful.
 */
- (void)getRefundDetails:(PPHInvoiceBasicCompletionHandler)completionHandler;

/*!
 Enqueues a network action to delete the invoice.
 @param completionHandler PPHInvoiceBasicCompletionHandler The block to invoke once the network response is processed, you can check the returned error to see if the request was successful.
 */
- (void)deleteInvoice:(PPHInvoiceBasicCompletionHandler)completionHandler;

@end